/* Bespin mac-a-like XBar KDE4
   Copyright (C) 2007 Thomas Luebking <thomas.luebking@web.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
 */

#include <QAbstractEventDispatcher>
#include <QApplication>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDesktopWidget>
#include <QDomElement>
#include <QFile>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QLabel>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QSettings>
#include <QStyle>
#include <QStyleOption>
#include <QTimer>
#include <QWidgetAction>
#include <QX11Info>

#include <kglobalsettings.h>
#include <kwindowsystem.h>
#include <kwindowinfo.h>
#include <KDirWatch>
#include <KIcon>
#include <KStandardDirs>
#include <KUriFilterData>
#include <KRun>

#include <Plasma/Containment>
#include <Plasma/Theme>

#include <limits.h>

// #include "button.h"
#include "menubar.h"
#include "xbar.h"
#include "dbus.h"

#include <QtDebug>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

static XBar *instance = NULL;

class DummyWidget : public QWidget
{
public:
    DummyWidget( QWidget * parent = 0, Qt::WindowFlags f = 0) : QWidget(parent, Qt::X11BypassWindowManagerHint)
    {
        Q_UNUSED(f);
    }
protected:
    void paintEvent(QPaintEvent *)
    {
        if (instance && instance->d.currentBar)
            instance->d.currentBar->update();
    }
};

static DummyWidget *dummy = NULL;

QTimer XBar::bodyCleaner;

static Atom ggmContext;
static Atom ggmEvent;
static QAbstractEventDispatcher::EventFilter formerX11EventFilter = 0;

static void ggmSetLocalMenus(bool on)
{
    Atom ggmSettings = XInternAtom( QX11Info::display(), "_NET_GLOBALMENU_SETTINGS", false );
    XTextProperty text;
    QString string = QString("\n[GlobalMenu:Client]\nshow-local-menu=%1\nshow-menu-icons=true\nchanged-notify-timeout=500\n").arg(on?"true":"false");
    QByteArray ba = string.toLatin1();
    ba.append("\0");
    char *data = ba.data();
    XStringListToTextProperty( &data, 1, &text );
    XSetTextProperty( QX11Info::display(), QX11Info::appRootWindow(), &text, ggmSettings );
}

XBar::XBar(QObject *parent, const QVariantList &args) : Plasma::Applet(parent, args)
{
    myMainMenu = 0;
    myMainMenuDefWatcher = 0;
    d.currentBar = 0; // important!
    dummy = 0;
    if (instance)
    {
        QMessageBox::warning ( 0, "Multiple XBar requests", "XBar shall be unique dummy text");
        qWarning("XBar, Do NOT load XBar more than once!");
        deleteLater();
    }
    else
    {
        instance = this;
    }
}

XBar::~XBar()
{
    if (instance == this)
    {
        byeMenus();
        instance = NULL;
        delete dummy; dummy = NULL;
    }
}

void
XBar::init()
{
    if (this != instance)
        return;
    if (!view())
    {
        QTimer::singleShot(100, this, SLOT(init()));
        return;
    }

    if (QGraphicsLinearLayout *lLayout = dynamic_cast<QGraphicsLinearLayout*>(containment()->layout()))
    {
        lLayout->setStretchFactor(this, 1000);
        lLayout->setAlignment( this, Qt::AlignLeft|Qt::AlignVCenter );
    }
    
//     if (!view()->inherits("PanelView"))
//     {
//         QMessageBox::warning ( 0, "XBar requires a Panel", "XBar shall be on panels dummy text");
//         qWarning("XBar, Do NOT use XBar on Desktop widgets!");
//         deleteLater();
//         return;
//     }
    dummy = new DummyWidget();
    dummy->setGeometry(5000,5000,1,1);
    dummy->show();
    
//     Plasma::Applet::init();
    //TODO : Qt's bug??
    setAspectRatioMode(Plasma::IgnoreAspectRatio);
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));
    setMaximumSize(INT_MAX, INT_MAX);

//     setFlag(ItemClipsChildrenToShape); setFlag(ItemClipsToShape);
    
    // TODO: use plasmoid popup and make this dynamic -> update all menubars...
    QSettings settings("Bespin", "XBar");
    settings.beginGroup("XBar");
    double scale = settings.value("FontScale", 1.0f).toDouble();
    if (scale > 0.0 && scale != 1.0)
    {
        myFont = KGlobalSettings::menuFont();
        myFont.setPointSize(scale*myFont.pointSize());
        setFont(myFont);
    }
    d.extraTitle = false; //settings.value("WindowList", false).toBool();

    repopulateMainMenu();
    
    d.currentBar = myMainMenu;

    updatePalette();
    
    show(myMainMenu);
    QTimer::singleShot(500, this, SLOT(showMainMenu())); // force repositioning cause plasma sucks.

    ggmLastId = 0;
    ggmContext = XInternAtom( QX11Info::display(), "_NET_GLOBALMENU_MENU_CONTEXT", false );
    ggmEvent = XInternAtom( QX11Info::display(), "_NET_GLOBALMENU_MENU_EVENT", false );
    formerX11EventFilter = QAbstractEventDispatcher::instance()->setEventFilter(globalX11EventFilter);

    connect( KWindowSystem::self(), SIGNAL( activeWindowChanged(WId) ), this, SLOT( ggmWindowActivated(WId) ) );
    connect( KWindowSystem::self(), SIGNAL( windowAdded(WId) ), this, SLOT( ggmWindowAdded(WId) ) );
    connect( KWindowSystem::self(), SIGNAL( windowRemoved(WId) ), this, SLOT( ggmWindowRemoved(WId) ) );
    
    new XBarAdaptor(this);
    QDBusConnection::sessionBus().registerService("org.kde.XBar");
    QDBusConnection::sessionBus().registerObject("/XBar", this);
    
    connect (this, SIGNAL(destroyed()), this, SLOT(byeMenus()));
    connect (qApp, SIGNAL(aboutToQuit()), this, SLOT(byeMenus()));
    connect (&d.windowList, SIGNAL(aboutToShow()), this, SLOT(updateWindowlist()));
    connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), this, SLOT(updatePalette()));
    connect (&bodyCleaner, SIGNAL(timeout()), this, SLOT(cleanBodies()));
    bodyCleaner.start(30000); // every 5 minutes - it's just to clean menus from crashed windows, so users won't constantly scroll them
    callMenus();
    // activate ggm ...
    ggmSetLocalMenus(false);
    foreach ( WId id, KWindowSystem::windows() )
        ggmWindowAdded( id );
}

void
XBar::updatePalette()
{
    QColor fg = Plasma::Theme::defaultTheme()->color(Plasma::Theme::TextColor);
    QColor bg = Plasma::Theme::defaultTheme()->color(Plasma::Theme::BackgroundColor);
    QPalette pal(fg, bg, Qt::white, Qt::black, Qt::gray, fg, fg, bg, bg );
    pal.setColor(QPalette::ButtonText, fg);
    setPalette(pal);
    myMainMenu->setPalette(pal);
    foreach (MenuBar *menu, d.menus)
        menu->setPalette(pal);
    d.windowList.setPalette(QApplication::palette());
}

void
XBar::activateWin()
{
    if (QAction *act = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int id = act->data().toUInt(&ok);
        if (ok)
            KWindowSystem::activateWindow( id );
    }
}

void
XBar::byeMenus()
{
    QDBusConnectionInterface *session = QDBusConnection::sessionBus().interface();
    QStringList services = session->registeredServiceNames();
    foreach ( QString service, services ) 
    {
        if ( service.startsWith("org.kde.XBar-") ) 
        {
            QDBusInterface interface( service, "/XBarClient", "org.kde.XBarClient" );
            if ( interface.isValid() )
                interface.call("deactivate");
        }
    }
    ggmSetLocalMenus(true);
}

void
XBar::callMenus()
{
   QDBusConnectionInterface *session = QDBusConnection::sessionBus().interface();
   QStringList services = session->registeredServiceNames();

   foreach (QString service, services) {
      if (service.startsWith("org.kde.XBar-")) {
         QDBusInterface interface( service, "/XBarClient", "org.kde.XBarClient" );
         if (interface.isValid()) {
            interface.call("activate");
         }
      }
   }
}

void
XBar::changeEntry(qlonglong key, int idx, const QString &entry, bool add)
{
    MenuMap::iterator i = d.menus.find( key );
    if (i == d.menus.end())
        return;

    MenuBar *bar = i.value();
    if (entry.isNull())
    {   // delete
        if (idx < 0)
            return;
        bar->removeAction(idx + d.extraTitle);
    }
    else if (add)
        bar->addAction(entry, idx < 0 ? -1 : idx + d.extraTitle);
    else
    {
        if (idx < 0)
            return;
        bar->changeAction(idx + d.extraTitle, entry);
    }
}

void
XBar::cleanBodies()
{
    QDBusConnectionInterface *session = QDBusConnection::sessionBus().interface();
    QStringList services = session->registeredServiceNames();
    services = services.filter(QRegExp("^org\\.kde\\.XBar-"));
    MenuMap::iterator i = d.menus.begin();
    MenuBar *mBar = 0;
    while (i != d.menus.end())
    {
        if (ggmMenus.contains(i.key()) || services.contains(i.value()->service()))
            ++i;
        else
        {
            mBar = i.value();
            if ( mBar == d.currentBar )
            {
                hide(mBar);
                show(myMainMenu);
            }
            i = d.menus.erase(i);
            delete mBar;
        }
    }
}

bool
XBar::dbusAction(const QObject *o, int idx, const QString &cmd)
{
    const MenuBar *mBar = qobject_cast<const MenuBar*>(o);
    if (!mBar)
        return false; // that's not our business!
    if (idx > -1)
    {
        QAction *act = mBar->action(idx);
        if (!act || act->menu())
            return false; // that's not our business!
    }

    QPoint pt = mapToGlobal(mBar->actionGeometry(idx).bottomLeft() + mBar->pos());

    QDBusInterface interface( mBar->service(), "/XBarClient", "org.kde.XBarClient" );
    if (interface.isValid())
    {
        if (idx < 0)
            interface.call(cmd, mBar->key());
        else
            interface.call(cmd, mBar->key(), idx - d.extraTitle, pt.x(), pt.y());
    }
    return true;
}

void
XBar::hide(MenuBar *item)
{
    item->hide();
}

void
XBar::hover(int idx)
{
    dbusAction(sender(), idx, "hover");
}

QPoint
XBar::mapToGlobal(const QPointF &pt)
{
    return view()->mapToGlobal(view()->mapFromScene(mapToScene(pt)));
}

void
XBar::raiseCurrentWindow()
{
    if (!d.currentBar || d.currentBar == myMainMenu)
        return; // nothing to raise...
    dbusAction(d.currentBar, -1, "raise");
}

void
XBar::registerMenu(const QString &service, qlonglong key, const QString &title, const QStringList &entries)
{
    MenuBar *newBar = new MenuBar(service, key, this, dummy);
    newBar->setAppTitle(title);
    newBar->setPalette(palette());
    newBar->setFont(myFont);
    connect (newBar, SIGNAL(hovered(int)), this, SLOT(hover(int)));
    connect (newBar, SIGNAL(triggered(int)), this, SLOT(trigger(int)));

    if (d.extraTitle)
    {   // the windowlist entry
        QAction *act = newBar->addAction( title );
        act->setMenu(&d.windowList);
    }

    // the demanded menu entries
    foreach (QString entry, entries)
        newBar->addAction(entry);


    // replace older versions - in case
    delete d.menus.take( key );
    d.menus.insert( key, newBar );

    // add hidden
    newBar->hide();
}

void
XBar::releaseFocus(qlonglong key)
{
    int n = 0;
    for (MenuMap::iterator i = d.menus.begin(); i != d.menus.end(); ++i)
    {
        if (i.key() == key)
            hide(i.value());
        else
            n += i.value()->isVisible();
    }
    if (!n)
    {
        d.currentBar = myMainMenu;
        show(myMainMenu);
    }
}

void
XBar::reparent(qlonglong oldKey, qlonglong newKey)
{
    MenuMap::iterator i = d.menus.find( oldKey );
    if (i == d.menus.end())
        return;
    MenuBar *bar = i.value();
    d.menus.erase(i);
    d.menus.insert(newKey, bar);
}

#define LABEL_ERROR "missing \"label\" attribute"
#define MENU_FUNC(_FUNC_) menu ? menu->_FUNC_ : menubar->_FUNC_

void
XBar::runFromAction()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action)
        return;
    const QString &command = action->data().toString();
    KUriFilterData execLineData( command );
    KUriFilter::self()->filterUri( execLineData, QStringList() << "kurisearchfilter" << "kshorturifilter" );
    QString cmd = ( execLineData.uri().isLocalFile() ? execLineData.uri().path() : execLineData.uri().url() );
    
    if ( cmd.isEmpty() )
        return;
    
    switch( execLineData.uriType() )
    {
        case KUriFilterData::LocalFile:
        case KUriFilterData::LocalDir:
        case KUriFilterData::NetProtocol:
        case KUriFilterData::Help:
        {
            new KRun( execLineData.uri(), 0 );
            break;
        }
        case KUriFilterData::Executable:
        case KUriFilterData::Shell:
        {
            QString args = cmd;
            if( execLineData.hasArgsAndOptions() )
                cmd += execLineData.argsAndOptions();
            KRun::runCommand( cmd, args, "", 0 );
            break;
        }
        case KUriFilterData::Unknown:
        case KUriFilterData::Error:
        default:
            break;
    }
}

void
XBar::callFromAction()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action)
        return;
    const QString &instruction = action->data().toString();
    QStringList list = instruction.split(';');
    if (list.count() < 5)
    {
        qWarning("invalid dbus chain, must be: \"bus;service;path;interface;method[;arg1;arg2;...]\", bus is \"session\" or \"system\"");
        return;
    }
    
    QDBusInterface *caller = 0;
    if (list.at(0) == "session")
        caller = new QDBusInterface( list.at(1), list.at(2), list.at(3), QDBusConnection::sessionBus() );
    else if (list.at(0) == "system")
        caller = new QDBusInterface( list.at(1), list.at(2), list.at(3), QDBusConnection::systemBus() );
    else
    {
        qWarning("unknown bus, must be \"session\" or \"system\"");
        return;
    }
    
    QList<QVariant> args;
    if (list.count() > 5)
    {
        for (int i = 5; i < list.count(); ++i)
        {
            bool ok = false;
            short Short = list.at(i).toShort(&ok);
            if (ok) { args << Short; continue; }
            unsigned short UShort = list.at(i).toUShort(&ok);
            if (ok) { args << UShort; continue; }
            int Int = list.at(i).toInt(&ok);
            if (ok) { args << Int; continue; }
            uint UInt = list.at(i).toUInt(&ok);
            if (ok) { args << UInt; continue; }
            double Double = list.at(i).toDouble(&ok);
            if (ok) { args << Double; continue; }
            
            args << list.at(i);
        }
    }
    caller->asyncCallWithArgumentList(list.at(4), args);
    delete caller;
}

void
XBar::rBuildMenu(const QDomElement &node, QObject *widget)
{
    MenuBar *menubar = 0;
    QMenu *menu = qobject_cast<QMenu*>(widget);
    if (!menu)
    {
        menubar = qobject_cast<MenuBar*>(widget);
        if (!menubar)
            return;
    }
    
    QDomNode kid = node.firstChild();
    while(!kid.isNull())
    {
        QDomElement e = kid.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            if (e.tagName() == "menu")
            {
                QString type = e.attribute("menu");
                if (!type.isEmpty())
                    buildMenu(type, widget, "submenu");
                else
                {
                    QMenu *newMenu = MENU_FUNC(addMenu(e.attribute("label", LABEL_ERROR)));
                    rBuildMenu(e, newMenu);
                }
            }
            else if (e.tagName() == "action")
            {
                QAction *action = new QAction(widget);
                QString cmd = e.attribute("dbus");
                if (!cmd.isEmpty())
                    connect ( action, SIGNAL(triggered()), SLOT(callFromAction()) );
                else
                {
                    cmd = e.attribute("exec");
                    if (cmd.isEmpty())
                    {
                        cmd = KGlobal::dirs()->locate("services", e.attribute("service") + ".desktop");
                        if (!cmd.isEmpty())
                        {
                            KService kservice(cmd);
                            action->setIcon(KIcon(kservice.icon()));
                            action->setText(kservice.name());
                            cmd = kservice.desktopEntryName();
                        }
                    }
                    if (!cmd.isEmpty())
                        connect ( action, SIGNAL(triggered()), SLOT(runFromAction()) );
                    else
                        qWarning("MainMenu action without effect, add \"dbus\" or \"exec\" attribute!");
                }
                action->setData(cmd);
                if (action->text().isEmpty())
                    action->setText(e.attribute("label", LABEL_ERROR));
                QString icn = e.attribute("icon");
                if (!icn.isEmpty())
                    action->setIcon(KIcon(icn));
                MENU_FUNC(addAction(action));
            }
            else if (e.tagName() == "separator")
                MENU_FUNC(addSeparator());
        }
        kid = kid.nextSibling();
    }
}


void
XBar::buildMenu(const QString &name, QObject *widget, const QString &type)
{
    if (!instance)
        return;
    
    QDomDocument menu(name);
    QFile file(KGlobal::dirs()->locate("data", "XBar/" + name + ".xml"));
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!menu.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    
    QDomElement element = menu.documentElement();
    if (!element.isNull() /*&& element.tagName() == type*/)
        instance->rBuildMenu(element, widget);
}

void
XBar::repopulateMainMenu()
{
    if (d.currentBar == myMainMenu)
        d.currentBar = 0;
    delete myMainMenu;
    myMainMenu = new MenuBar("", 0, this, dummy);
    myMainMenu->setFont(myFont);
    myMainMenu->setAppTitle("Plasma");
    myMainMenu->addAction("Plasma",-1, &d.windowList);

    delete myMainMenuDefWatcher;

    QString xmlPath = KGlobal::dirs()->locate("data", "XBar/MainMenu.xml");
    QFile xmlFile(xmlPath);
    if (xmlFile.open(QIODevice::ReadOnly))
    {
        xmlFile.close();
        buildMenu("MainMenu", myMainMenu, "menubar");
    }
    else
    {
        QAction *action = new QAction(myMainMenu);
        action->setText("Customizable menu, see http://CloudCity.SF.net/xbar.html");
        action->setData("http://CloudCity.SF.net/xbar.html");
        connect ( action, SIGNAL(triggered()), SLOT(runFromAction()) );
        myMainMenu->addAction(action);
    }
    
    if (xmlPath.isNull())
        xmlPath = KGlobal::dirs()->locate("data", "XBar");
    myMainMenuDefWatcher = new KDirWatch(this);
    myMainMenuDefWatcher->addFile(xmlPath);
    connect( myMainMenuDefWatcher, SIGNAL(created(const QString &)), this, SLOT(repopulateMainMenu()) );
    connect( myMainMenuDefWatcher, SIGNAL(deleted(const QString &)), this, SLOT(repopulateMainMenu()) );
    connect( myMainMenuDefWatcher, SIGNAL(dirty(const QString &)), this, SLOT(repopulateMainMenu()) );

    if (d.currentBar)
        myMainMenu->hide();
    else
        d.currentBar = myMainMenu;
}

void
XBar::requestFocus(qlonglong key)
{
    for (MenuMap::iterator i = d.menus.begin(); i != d.menus.end(); ++i)
    {
        if (i.key() == key)
        {
            hide(myMainMenu);
            if ( !i.value()->isEnabled() && ggmMenus.contains( key ) )
            {   // invalidated
                delete i.value();
                i.value() = ggmCreate( key );
                if (!i.value())
                {
                    d.menus.erase( i );
                    ggmMenus.removeAll( key );
                    show(myMainMenu); // invalid attempt
                    return;
                }
            }
            show(i.value());
        }
        else
            hide(i.value());
    }
}

void
XBar::setOpenPopup(int idx)
{
    if (d.currentBar && d.currentBar != myMainMenu)
    {
        d.currentBar->setOpenPopup(idx + d.extraTitle);
        d.currentBar->update();
    }
}

QSizeF
XBar::sizeHint ( Qt::SizeHint which, const QSizeF & constraint ) const
{
    if (d.currentBar)
        return d.currentBar->sizeHint(which, constraint);
    return QSizeF(1,1);
}

void
XBar::show(MenuBar *item)
{
    d.currentBar = item;
    int dy = (contentsRect().height() - item->rect().height())/2;
    item->setPos(contentsRect().x(), contentsRect().y()+dy);
    item->show();
}

void
XBar::showMainMenu()
{
    foreach (MenuBar *menu, d.menus)
        hide(menu);

    d.currentBar = myMainMenu;
    show(myMainMenu);
    if (view())
        view()->activateWindow();
    update();
}


void
XBar::trigger(int idx)
{
    dbusAction(sender(), idx, "popup");
}

void
XBar::unregisterMenu(qlonglong key)
{
    releaseFocus(key);
    delete d.menus.take( key );
}

void
XBar::unregisterCurrentMenu()
{
    if (!d.currentBar || d.currentBar == myMainMenu)
        return;
    qlonglong key = d.menus.key(d.currentBar, 0);
    if (key)
    {
        QDBusInterface interface( d.currentBar->service(), "/XBarClient", "org.kde.XBarClient" );
        if (interface.isValid())
            interface.call("deactivate");
        unregisterMenu(key);
    }
}


void
XBar::setCurrentDesktop()
{
    if ( QAction *act = qobject_cast<QAction*>(sender()) )
        KWindowSystem::setCurrentDesktop(act->data().toInt());
}

void
XBar::updateWindowlist()
{
    d.windowList.clear();
    
    KWindowInfo info;
    int currentDesktop = KWindowSystem::currentDesktop();
    int n = KWindowSystem::numberOfDesktops();
    QList<WId> *windowTable = new QList<WId>[n];
    
    const QList<WId>& windows = KWindowSystem::windows();
    foreach (WId id, windows)
    {
        info = KWindowInfo(id, NET::WMDesktop | NET::WMWindowType, 0);
        if (info.windowType( NET::NormalMask | NET::DialogMask | NET::UtilityMask ) != -1)
            if (int d = info.desktop())
            {
                if (info.onAllDesktops()) d = currentDesktop;
                windowTable[d-1].append(id);
            }
    }
    
    QAction *act(0);
    int desk;
    bool needSep = false;
    for (int i = 0; i < n; ++i)
    {
        desk = i+1;
        
        if (needSep)
            d.windowList.addSeparator();
        if ( desk == KWindowSystem::currentDesktop() )
        {
            //             d.windowList.addSeparator()->setText(KWindowSystem::desktopName(d));
            // because QMenu cannot handle text separators right, patch submitted
            QLabel *dummy = new QLabel(KWindowSystem::desktopName(desk), &d.windowList);
            QWidgetAction *dummyAction = new QWidgetAction( &d.windowList );
            dummyAction->setDefaultWidget( dummy );
            d.windowList.addAction( dummyAction );
            dummy->setAlignment( Qt::AlignCenter );
            QPalette pal = d.windowList.palette();
            pal.setColor( QPalette::WindowText, pal.color(d.windowList.foregroundRole()) );
            dummy->setPalette(pal);
            QFont fnt = d.windowList.font();
            fnt.setPointSize( fnt.pointSize() * 1.4 );
            fnt.setBold(true);
            dummy->setFont(fnt);
            //----------------------
        }
        else
        {
            act = d.windowList.addAction( KWindowSystem::desktopName(desk), this, SLOT(setCurrentDesktop()) );
            act->setData(desk);
            if (i < n-1)
                d.windowList.addSeparator();
        }
        
        needSep = false;
        foreach (WId id, windowTable[i])
        {
            info = KWindowInfo(id, NET::WMVisibleIconName | NET::WMState | NET::XAWMState, 0);
            {
                if (info.hasState(NET::SkipTaskbar))
                    continue;
                QString title = info.visibleIconName();
                if (info.isMinimized())
                    title = "( " + title + " )";
                title = "    " + title;
                if (title.length() > 52)
                    title = title.left(22) + "..." + title.right(22);
                act = d.windowList.addAction( KWindowSystem::icon(id, 32, 32, false ), title, this, SLOT(activateWin()) );
                act->setData((uint)id);
                act->setDisabled(id == KWindowSystem::activeWindow());
                needSep = true;
            }
        }
    }
    delete[] windowTable;
#if 0
    d.windowList.clear();

    d.windowList.addAction ( "Raise Window", this, SLOT(raiseCurrentWindow()) );
    d.windowList.addSeparator();
//    d.windowList.addAction ( "Show Taskbar", this, SLOT(showTaskbar()) );
//    d.windowList.addSeparator();
   
    const QList<WId>& windows = KWindowSystem::windows();
    QAction *act = 0;
    KWindowInfo info; QString title;
    #define NET_FLAGS NET::WMVisibleIconName | NET::WMWindowType | NET::WMDesktop | NET::WMState | NET::XAWMState

    foreach (WId id, windows)
    {
        info = KWindowInfo(id, NET_FLAGS, 0);
        if (info.windowType( NET::NormalMask | NET::DialogMask | NET::UtilityMask ) != -1) {
            title = info.visibleIconName();
            if (info.isMinimized())
                title = "( " + title + " )";
            if (!info.isOnCurrentDesktop())
                title = "< " + title + " >";
            if (title.length() > 52)
                title = title.left(22) + "..." + title.right(22);
            act = d.windowList.addAction ( title, this, SLOT(activateWin()) );
            act->setData((uint)id);
            act->setDisabled(id == KWindowSystem::activeWindow());
        }
    }
    d.windowList.setTitle("Windows");
    d.windowList.addSeparator();
    d.windowList.addAction ( "Embed menu in window", this, SLOT(unregisterCurrentMenu()) );
#endif
}

void
XBar::wheelEvent(QGraphicsSceneWheelEvent *ev)
{
    if (d.menus.isEmpty())
        return;

    if (view())
        view()->activateWindow();

    MenuMap::iterator n;

    if (d.currentBar == myMainMenu)
    {
        hide(myMainMenu);
        if (ev->delta() < 0)
            n = d.menus.begin();
        else
            { n = d.menus.end(); --n; }
    }
    else {
        n = d.menus.end();
        MenuMap::iterator i = d.menus.end();
        for (i = d.menus.begin(); i != d.menus.end(); ++i)
        {
            hide(i.value());
            if (i.value() == d.currentBar)
            {
                if (ev->delta() < 0)
                    n = i+1;
                else if (i == d.menus.begin())
                    n = d.menus.end();
                else
                    n = i-1;
            }
        }
    }
    
    while ( n != d.menus.end() && !n.value()->isEnabled() && ggmMenus.contains( n.key() ) )
    {   // update invalidated menus - we might have lost them as well...
        delete n.value();
        n.value() = ggmCreate( n.key() );
        if (n.value())
            break;
        else
        {
            ggmMenus.removeAll( n.key() );
            n = d.menus.erase( n );
        }
    }

    if (n == d.menus.end())
        show(myMainMenu);
    else
        show( n.value() );
}


// ================= GGM support implementation ===============


static QHash<QString,QString> ggmMapIcons()
{
    QHash<QString,QString> hash;
    hash.insert( "gtk-about", "start-here-kde" );
    hash.insert( "gtk-add", "list-add.png" );
    hash.insert( "gtk-apply", "dialog-ok-apply.png" );
    hash.insert( "gtk-bold", "format-text-bold.png" );
    hash.insert( "gtk-cancel", "dialog-cancel.png" );
    hash.insert( "gtk-cdrom", "media-optical.png" );
    hash.insert( "gtk-clear", "edit-clear.png" );
    hash.insert( "gtk-close", "window-close.png" );
    hash.insert( "gtk-color-picker", "color-picker.png" );
    hash.insert( "gtk-connect", "network-connect.png" );
    hash.insert( "gtk-convert", "document-export.png" );
    hash.insert( "gtk-copy", "edit-copy.png" );
    hash.insert( "gtk-cut", "edit-cut.png" );
    hash.insert( "gtk-delete", "edit-delete.png" );
    hash.insert( "gtk-dialog-authentication", "status/dialog-password.png" );
    hash.insert( "gtk-dialog-error", "status/dialog-error.png" );
    hash.insert( "gtk-dialog-info", "status/dialog-information.png" );
    hash.insert( "gtk-dialog-question", "status/dialog-information.png" );
    hash.insert( "gtk-dialog-warning", "status/dialog-warning.png" );
    hash.insert( "gtk-directory", "folder.png" );
    hash.insert( "gtk-disconnect", "network-disconnect.png" );
    hash.insert( "gtk-dnd", "application-x-zerosize.png" );
    hash.insert( "gtk-dnd-multiple", "document-multiple.png" );
    hash.insert( "gtk-edit", "document-properties.png" );
    hash.insert( "gtk-execute", "fork.png" );
    hash.insert( "gtk-file", "application-x-zerosize.png" );
    hash.insert( "gtk-find", "edit-find.png" );
    hash.insert( "gtk-find-and-replace", "edit-find-replace.png" );
    hash.insert( "gtk-floppy", "media-floppy.png" );
    hash.insert( "gtk-fullscreen", "view-fullscreen.png" );
    hash.insert( "gtk-goto-bottom", "go-bottom.png" );
    hash.insert( "gtk-goto-first", "go-first.png" );
    hash.insert( "gtk-goto-last", "go-last.png" );
    hash.insert( "gtk-goto-top", "go-top.png" );
    hash.insert( "gtk-go-back", "go-previous.png" );
    hash.insert( "gtk-go-back-ltr", "go-previous.png" );
    hash.insert( "gtk-go-back-rtl", "go-next.png" );
    hash.insert( "gtk-go-down", "go-down.png" );
    hash.insert( "gtk-go-forward", "go-next.png" );
    hash.insert( "gtk-go-forward-ltr", "go-next.png" );
    hash.insert( "gtk-go-forward-rtl", "go-previous.png" );
    hash.insert( "gtk-go-up", "go-up.png" );
    hash.insert( "gtk-harddisk", "drive-harddisk.png" );
    hash.insert( "gtk-help", "help-contents.png" );
    hash.insert( "gtk-home", "go-home.png" );
    hash.insert( "gtk-indent", "format-indent-more.png" );
    hash.insert( "gtk-index", "help-contents.png" );
    hash.insert( "gtk-info", "help-about.png" );
    hash.insert( "gtk-italic", "format-text-italic.png" );
    hash.insert( "gtk-jump-to", "go-jump.png" );
    hash.insert( "gtk-justify-center", "format-justify-center.png" );
    hash.insert( "gtk-justify-fill", "format-justify-fill.png" );
    hash.insert( "gtk-justify-left", "format-justify-left.png" );
    hash.insert( "gtk-justify-right", "format-justify-right.png" );
    hash.insert( "gtk-leave-fullscreen", "view-restore.png" );
    hash.insert( "gtk-media-forward", "media-seek-forward.png" );
    hash.insert( "gtk-media-next", "media-skip-forward.png" );
    hash.insert( "gtk-media-pause", "media-playback-pause.png" );
    hash.insert( "gtk-media-play", "media-playback-start.png" );
    hash.insert( "gtk-media-previous", "media-skip-backward.png" );
    hash.insert( "gtk-media-record", "media-record.png" );
    hash.insert( "gtk-media-rewind", "media-seek-backward.png" );
    hash.insert( "gtk-media-stop", "media-playback-stop.png" );
    hash.insert( "gtk-missing-image", "unknown.png" );
    hash.insert( "gtk-network", "network-server.png" );
    hash.insert( "gtk-new", "document-new.png" );
    hash.insert( "gtk-no", "edit-delete.png" );
    hash.insert( "gtk-ok", "dialog-ok.png" );
    hash.insert( "gtk-open", "document-open.png" );
    hash.insert( "gtk-paste", "edit-paste.png" );
    hash.insert( "gtk-preferences", "configure.png" );
    hash.insert( "gtk-print", "document-print.png" );
    hash.insert( "gtk-print-preview", "document-print-preview.png" );
    hash.insert( "gtk-properties", "document-properties.png" );
    hash.insert( "gtk-quit", "application-exit.png" );
    hash.insert( "gtk-redo", "edit-redo.png" );
    hash.insert( "gtk-refresh", "view-refresh.png" );
    hash.insert( "gtk-remove", "edit-delete.png" );
    hash.insert( "gtk-revert-to-saved", "document-revert.png" );
    hash.insert( "gtk-save", "document-save.png" );
    hash.insert( "gtk-save-as", "document-save-as.png" );
    hash.insert( "gtk-select-all", "edit-select-all.png" );
    hash.insert( "gtk-select-color", "color-picker.png" );
    hash.insert( "gtk-select-font", "preferences-desktop-font.png" );
    hash.insert( "gtk-sort-ascending", "view-sort-ascending.png" );
    hash.insert( "gtk-sort-descending", "view-sort-descending.png" );
    hash.insert( "gtk-spell-check", "tools-check-spelling.png" );
    hash.insert( "gtk-stop", "process-stop.png" );
    hash.insert( "gtk-strikethrough", "format-text-strikethrough.png" );
    hash.insert( "gtk-undelete", "edit-undo.png" );
    hash.insert( "gtk-underline", "format-text-underline.png" );
    hash.insert( "gtk-undo", "edit-undo.png" );
    hash.insert( "gtk-unindent", "format-indent-less.png" );
    hash.insert( "gtk-yes", "dialog-ok.png" );
    hash.insert( "gtk-zoom-100", "zoom-original.png" );
    hash.insert( "gtk-zoom-fit", "zoom-fit-best.png" );
    hash.insert( "gtk-zoom-in", "zoom-in.png" );
    hash.insert( "gtk-zoom-out", "zoom-out.png" );
    return hash;
}

static QHash<QString,QString> ggmIconMap = ggmMapIcons();

bool
XBar::globalX11EventFilter( void *msg )
{
    XEvent *ev = static_cast<XEvent*>(msg);
    if (instance && ev && ev->type == PropertyNotify)
    {
        if (ev->xproperty.atom == ggmContext)
            instance->ggmUpdate( ev->xproperty.window );
        //         else if (ev->xproperty.atom == mEvtAtom)
        //             qDebug() << "Evt:" << QString::number(ev->xproperty.window) << XGetAtomName(QX11Info::display(),ev->xproperty.atom);
    }
    return formerX11EventFilter && (formerX11EventFilter)( msg );
}

#define MENU_FUNC(_FUNC_) menu ? menu->_FUNC_ : menubar->_FUNC_

static inline QString accelMappedLabel( const QDomElement &node )
{
    // escape "&", replace "_" accels by "&"
    return node.attribute("label").replace('&', "&&").replace(QRegExp("_([^_])"), "&\\1");
}

void
ggmRecursive(const QDomElement &node, QObject *widget, const QString &prefix )
{
    if ( node.isNull() )
        return;
    
    MenuBar *menubar = 0;
    QMenu *menu = qobject_cast<QMenu*>(widget);
    if (!menu)
    {
        menubar = qobject_cast<MenuBar*>(widget);
        if (!menubar)
            return;
    }
    
    QDomElement e = node.firstChildElement("item");
    while ( !e.isNull() )
    {
        if (e.attribute("visible") != "0" )
        {
            if (e.attribute("type") == "s")
                MENU_FUNC( addSeparator() );
            else
            {
                QDomElement menuNode = e.firstChildElement("menu");
                if ( !menuNode.isNull() )
                {   // submenu
                    QMenu *newMenu = MENU_FUNC( addMenu( accelMappedLabel(e) ) );
                    ggmRecursive(menuNode, newMenu, prefix + "/" + e.attribute("id") );
                }
                else if ( !e.attribute("label").isEmpty() )
                {   // real action item
                    QAction *action = new QAction(widget);
                    action->setText( accelMappedLabel(e) );
                    action->setData( prefix + "/" + e.attribute("id") );
                    action->setEnabled( e.attribute("sensible") != "0" );
                    QString icon = e.attribute("icon");
                    if ( !icon.isEmpty() ) 
                        icon = ggmIconMap.value( icon, QString() );
                    if ( !icon.isEmpty() ) 
                        action->setIcon( KIcon( icon ) );
                    QString state = e.attribute("state");
                    int iState = 0;
                    if ( state == "0" )
                        iState = 1;
                    else if ( state == "1" )
                        iState = 2;
                    action->setCheckable( iState > 0 );
                    action->setChecked( (iState == 2) );
                    QObject::connect ( action, SIGNAL(triggered()), instance, SLOT(runGgmAction()) );
                    MENU_FUNC( addAction(action) );
                }
            }
        }
        e = e.nextSiblingElement("item");
    }
}

MenuBar *
XBar::ggmCreate( WId id )
{
    MenuBar *bar = 0;
    int nItems;
    char **list;
    XTextProperty string;
    
    if ( XGetTextProperty(QX11Info::display(), id, &string, ggmContext) && XTextPropertyToStringList(&string, &list, &nItems) )
    {
        if (nItems)
        {
            QString xml = QString::fromUtf8( list[0] );
            bar = new MenuBar("", 0, this, dummy);
            KWindowInfo info(id, 0, NET::WM2WindowClass);
            bar->setAppTitle(info.windowClassClass());
            bar->setPalette(palette());
            bar->setFont(myFont);
            QDomDocument doc;
            doc.setContent( xml, false );
            QDomElement root = doc.firstChildElement();
            ggmRecursive( root, bar, QString::number(id) );
            bar->hide();
        }
        XFreeStringList(list);
    }
    return bar;
}

void
XBar::ggmWindowActivated( WId id )
{
    while ( id && !ggmMenus.contains( id ) )
    {
        if ( KWindowInfo( id, NET::WMState ).state() & NET::Modal )
            id = 0;
        else
            id = KWindowSystem::transientFor(id);
    }
    
    if ( ggmMenus.contains( id ) )
    {
        ggmLastId = id;
        requestFocus( id );
    }
    else if ( ggmLastId )
    {
        releaseFocus( ggmLastId );
        ggmLastId = 0;
    }
}

void 
XBar::ggmUpdate( WId id )
{
    bool added = false, wasVisible = false;
    
    MenuMap::iterator it = d.menus.find( id );
    if ( it == d.menus.end() )
    {
        if ( MenuBar *bar = ggmCreate(id) )
            d.menus.insert( id, bar );
        else
            return; // there's no menu for us
    }
    else 
    {
        wasVisible = it.value()->isVisible();
        it.value()->setEnabled(false); // invalidate
    }

    if ( (added = !ggmMenus.contains( id )) )
        ggmMenus.append( id );
    if ( wasVisible || (added && KWindowSystem::activeWindow() == id) )
        requestFocus( id );
}

static const unsigned long supported_types = NET::NormalMask | NET::DialogMask | NET::OverrideMask | NET::UtilityMask;

void
XBar::ggmWindowAdded( WId id )
{
    KWindowInfo info( id, NET::WMWindowType );
    NET::WindowType type = info.windowType( supported_types );
    if ( type == NET::Unknown ) // everything that's not a supported_type
        return;
    foreach ( QWidget *w, QApplication::topLevelWidgets() )
    {
        if ( w->winId() == id )
            return;
    }
    XSelectInput( QX11Info::display(), id, PropertyChangeMask );
    qApp->syncX();
    ggmUpdate( id );
}

void
XBar::ggmWindowRemoved( WId id )
{
    int idx = ggmMenus.indexOf( id );
    if ( idx > -1 )
    {
        releaseFocus( id );
        delete d.menus.take( id );
        ggmMenus.removeAt( idx );
    }
}

void
XBar::runGgmAction()
{
    if ( QAction *act = qobject_cast<QAction*>(sender()) )
    {
        QString string = act->data().toString();
        int slash = string.indexOf('/');
        WId id = string.left(slash).toULongLong();
        string = string.mid(slash);
        //         qDebug() << id << string;
        char *data = string.toUtf8().append("\0").data();
        XTextProperty text;
        XStringListToTextProperty( &data, 1, &text );
        XSetTextProperty( QX11Info::display(), id, &text, ggmEvent );
    }
}


K_EXPORT_PLASMA_APPLET(xbar, XBar)

#include "dbus.moc"
#include "xbar.moc"
