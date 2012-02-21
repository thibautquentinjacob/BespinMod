/*
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
#include <QAction>
#include <QBasicTimer>
#include <QDBusInterface>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMenu>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionMenuItem>

#include <Plasma/Applet>

#include "menubar.h"
// #include "xbar.h"

#include <QtDebug>


static QBasicTimer mousePoll;
static QPointF lastMousePos;

MenuBar::MenuBar( const QString &service, qlonglong key, QGraphicsWidget *parent, QWidget *dummy) :
QGraphicsWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setAcceptHoverEvents(true);
    d.hoverIndex = -1;
    d.openPopup = -1;
    d.service = service;
    d.key = key;
    d.widget = dummy;
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    if (QGraphicsLinearLayout *lLayout = dynamic_cast<QGraphicsLinearLayout*>(parent->layout()))
    {
        lLayout->insertItem(0, this);
        lLayout->setAlignment(this, Qt::AlignCenter|Qt::AlignLeft);
    }
//     setFont();
//    setObjectName( "XBarMenubar" );
}

#if 0
MenuBar::~MenuBar()
{
    if (QGraphicsWidget *parentWidget = qobject_cast<QGraphicsWidget*>(parent()))
    if (QGraphicsLinearLayout *lLayout = dynamic_cast<QGraphicsLinearLayout*>(parentWidget->layout()))
        lLayout->removeItem(this);
}
#endif

QAction *
MenuBar::action(int idx) const
{
    if (idx > -1 && idx < d.actions.count())
        return d.actions.at(idx);
    return NULL;
}

QAction *
MenuBar::action(const QPoint &pos) const
{
    for (int i = 0; i < d.actionRects.count(); ++i)
        if (d.actionRects.at(i).contains(pos))
            return d.actions.at(i);

    return NULL;
}

// void
// MenuBar::show()
// {
//    d.sizeHint = QSize();
//    resize(sizeHint(Qt::PreferredSize));
//    QGraphicsWidget::show();
// }

QSizeF
MenuBar::sizeHint ( Qt::SizeHint which, const QSizeF & constraint ) const
{
    if ( which < Qt::MaximumSize )
        return d.preferredSize;
    return QSizeF( 1.67772e+07, 1.67772e+07 );
    // this is broken...
//     return QGraphicsWidget::sizeHint(which, constraint);
}


void
MenuBar::hide()
{
    popDown();
    setOpenPopup(-1);
    d.hoverIndex = -1;
    QGraphicsWidget::hide();
}

static QRect nullRect;

const QRect &
MenuBar::actionGeometry(int idx) const
{
    if (idx < 0 || idx >= d.actionRects.count())
        return nullRect;

    return d.actionRects.at(idx);
}

QAction *
MenuBar::addAction(const QString & text, int idx, QMenu *menu)
{
    QAction *ret = new QAction(text, this);
    if (text == "<XBAR_SEPARATOR/>")
        ret->setSeparator(true);
    addAction(ret, idx);
    ret->setMenu(menu);
    return ret;
}

void
MenuBar::addAction(QAction *action, int idx)
{
    if (idx < 0 || idx >= d.actions.count())
    {
        d.actions.append( action );
        d.actionRects.append(QRect());
    }
    else
    {
        d.actions.insert( idx, action );
        d.actionRects.insert(idx, QRect());
    }
    
    connect (action, SIGNAL(changed()), this, SLOT(actionChanged()));
    updateSize();
}

QAction *
MenuBar::addMenu(QMenu *menu)
{
    return addAction(menu->title(), -1, menu);
}

QMenu *
MenuBar::addMenu(const QString &title)
{
    QMenu *menu = new QMenu(d.widget);
    addAction(title, -1, menu);
    return menu;
}

QAction*
MenuBar::addSeparator()
{
    return addAction("<XBAR_SEPARATOR/>", -1);
}

void
MenuBar::actionChanged()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;
    for (int i = 0; i < d.actions.count(); ++i)
    {
        if (d.actions.at(i) == action)
        {
            d.actionRects[i] = QRect();
            break;
        }
    }
    updateSize();
    update();
}

void
MenuBar::changeAction(int idx, const QString & text)
{
    if (idx < 0 || idx >= d.actions.count())
    {
        qWarning("XBar, cannot change action with id %d - not present", idx);
        return;
    }

    QAction *act = d.actions.at(idx);
    act->setText(text);
    if (text == "<XBAR_SEPARATOR/>")
        act->setSeparator(true);
    d.actionRects[idx] = QRect();
    updateSize();
}

void
MenuBar::clear()
{
    foreach (QAction *action, d.actions)
        delete action;

    d.actions.clear();
    d.actionRects.clear();
}

int
MenuBar::index(const QPoint &pos)
{
    for (int i = 0; i < d.actionRects.count(); ++i)
        if (d.actionRects.at(i).contains(pos))
            return i;

   return -1;
}

void
MenuBar::initStyleOption(QStyleOptionMenuItem *option, int idx) const
{
    if (!option)
        return;

    option->palette = palette();
    option->menuRect = rect().toRect();
    int idxdata = (d.openPopup < 0) ? ((d.hoverIndex+1) << 16) : 0;
    idxdata |= ((idx+1) & 0xffff);
    option->menuItemType = (QStyleOptionMenuItem::MenuItemType)idxdata;
    option->checkType = QStyleOptionMenuItem::NotCheckable;

    option->state = QStyle::State_None;
    if (hasFocus())
        option->state |= QStyle::State_HasFocus;

    if (idx < 0)
        return;

    QAction *action = d.actions.at(idx);
    option->font = font(); //action->font();
    option->icon = action->icon();
    if (idx)
        option->text = action->text();
    else
    {
        option->text = d.appTitle;
        int lightX = QFontMetrics(option->font).xHeight();
        option->font.setWeight(QFont::Black);
//         option->font.setCapitalization ( QFont::AllUppercase );
        option->font.setPointSize((option->font.pointSize()*lightX)/QFontMetrics(option->font).xHeight());
    }
    option->fontMetrics = QFontMetrics(option->font);

    if (isEnabled() && action->isEnabled())
        option->state |= QStyle::State_Enabled;
    else
        option->palette.setCurrentColorGroup(QPalette::Disabled);


    if (idx == d.hoverIndex)
        option->state |= QStyle::State_Selected;
    if (idx == d.openPopup)
        option->state |= QStyle::State_Sunken;
}

void
MenuBar::hoverEnterEvent(QGraphicsSceneHoverEvent *ev)
{
    d.hoverIndex = -1;
    mouseMoved(ev->pos(), QPointF());
}

void
MenuBar::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    int idx = d.hoverIndex;
    d.hoverIndex = -1;
    if (idx > -1 && d.openPopup != idx)
        update(d.actionRects.at(idx));
}

void
MenuBar::hoverMoveEvent(QGraphicsSceneHoverEvent *ev)
{
    mouseMoved(ev->pos(), ev->lastPos());
}

QPointF
MenuBar::mapFromGlobal(const QPoint &pt)
{
    if (QGraphicsView *v = view())
        return mapFromScene(v->mapToScene(v->mapFromGlobal(pt)));
    return mapFromScene(pt).toPoint();
}

QPoint
MenuBar::mapToGlobal(const QPointF &pt)
{
    if (QGraphicsView *v = view())
        return v->mapToGlobal(v->mapFromScene(mapToScene(pt)));
    return mapToScene(pt).toPoint();
}

void
MenuBar::mouseMoved(const QPointF &pos, const QPointF &lastPos)
{
    int idx = index(pos.toPoint());

    if (idx > -1 && d.openPopup == idx)
        return;
    int lastIdx = index(lastPos.toPoint());

    if (idx == lastIdx)
        return;

    // hover, maybe trigger a popup
    d.hoverIndex = idx;

    if (d.openPopup > -1 && idx > -1)
    {
        if (QMenu* menu = d.actions.at(idx)->menu())
        {   // new is internal
            popDown(); // get rid of openpopup (might be external)
            setOpenPopup(idx); // trigger this
            const QPoint pt = mapToGlobal(d.actionRects.at(idx).bottomLeft());
            connect (menu, SIGNAL(aboutToHide()), this, SLOT(popupClosed()));
            menu->popup(pt);
        }
        else if (d.actions.at(d.openPopup)->menu()) { // popup was internal, new is not
            d.actions.at(d.openPopup)->menu()->close();
            emit triggered(idx);
        }
    }

    if (idx > -1)
        update(d.actionRects.at(idx));
    if (lastIdx > -1)
        update(d.actionRects.at(lastIdx));

    emit hovered(idx);
}

void
MenuBar::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    ev->ignore();
    int idx = index(ev->pos().toPoint());
    if (idx < 0)
        return;
    if (ev->button() == Qt::RightButton)
    {
        rightMouseButtonEvent(idx, ev);
        return;
    }
    if (ev->button() != Qt::LeftButton)
        return;

    ev->accept();
    if (QMenu* menu = d.actions.at(idx)->menu())
    {
        setOpenPopup(idx);
        const QPoint pt = mapToGlobal(d.actionRects.at(idx).bottomLeft());
        connect (menu, SIGNAL(aboutToHide()), this, SLOT(popupClosed()));
        menu->popup(pt);
        update(d.actionRects.at(idx));
    }
    d.actions.at(idx)->trigger();
    emit triggered(idx);
}

void
MenuBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QRegion emptyArea(rect().toRect());

    //draw the items
    QStyleOptionMenuItem opt;
    QRect adjustedActionRect;
    QAction *action;
    painter->save();
    for (int i = 0; i <  d.actions.count(); ++i)
    {
        action = d.actions.at(i);
        if (action->isSeparator())
            continue;
        adjustedActionRect = d.actionRects.at(i);
        if (adjustedActionRect.isEmpty() || !action->isVisible())
            continue;
        if(!option->exposedRect.intersects(adjustedActionRect))
            continue;

        emptyArea -= adjustedActionRect;
        initStyleOption(&opt, i);
        opt.rect = adjustedActionRect;
        painter->setFont(opt.font);
        painter->setClipRect(adjustedActionRect);
        style()->drawControl(QStyle::CE_MenuBarItem, &opt, painter, d.widget);
    }

    painter->setClipRegion(emptyArea);
    initStyleOption(&opt, -1);
    opt.menuItemType = QStyleOptionMenuItem::EmptyArea;
    opt.rect = rect().toRect();
    style()->drawControl(QStyle::CE_MenuBarEmptyArea, &opt, painter, d.widget);
    painter->restore();
}

void
MenuBar::popDown()
{
//    if (d.openPopup > -1) {

    QDBusInterface interface( d.service, "/XBarClient", "org.kde.XBarClient" );
    if (interface.isValid())
        interface.call(QDBus::NoBlock, "popDown", d.key);

    foreach (QAction *action, d.actions)
    {
        if (action->menu())
        action->menu()->close();
    }
//    }
   // yes - to stop timer in case!
    setOpenPopup(-1);
}

void
MenuBar::popupClosed()
{
    if (!sender())
        return;
    disconnect (sender(), SIGNAL(aboutToHide()), this, SLOT(popupClosed()));

    if (d.openPopup < 0)
        return;
    update(d.actionRects.at(d.openPopup));

    setOpenPopup(-1);
}

void
MenuBar::removeAction(int idx)
{
    if (idx < 0 || idx >= d.actions.count())
    {
        qWarning("XBar, cannot remove action with id %d - not present", idx);
        return;
    }
    delete d.actions.takeAt(idx);
    d.actionRects.removeAt(idx);
    updateSize();
}

void
MenuBar::setOpenPopup(int popup)
{
    d.openPopup = popup;
    if (popup < 0)
        mousePoll.stop();
    else
        mousePoll.start(50, this);
}

QAction *
MenuBar::takeAction(int idx)
{
    if (idx < 0 || idx >= d.actions.count())
    {
        qWarning("XBar, cannot take action with id %d - not present", idx);
        return NULL;
    }
    QAction *ret = d.actions.takeAt(idx);
    d.actionRects.removeAt(idx);
    updateSize();
    return ret;
}

void
MenuBar::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != mousePoll.timerId())
        return;
    QPointF pos = mapFromGlobal(QCursor::pos());
    if (pos != lastMousePos && rect().contains(pos))
        mouseMoved(pos, lastMousePos);
    lastMousePos = pos;
}

void
MenuBar::updateSize()
{
    int h = 0, w = 0;
    QRect r; QAction *action;
    MenuBar *that = const_cast<MenuBar*>(this);
    QStyleOptionMenuItem opt;
    for (int i = 0; i < d.actions.count(); ++i)
    {
        action = d.actions.at(i);
        if (action->isSeparator())
            continue;
        r = d.actionRects.at(i);
        if (!r.isValid())
        {
            initStyleOption(&opt, i);
            QFontMetrics fm(opt.font);
            r = fm.boundingRect(opt.text);
            r.setSize(style()->sizeFromContents(QStyle::CT_MenuBarItem, &opt, r.size(), 0));
        }
        r.moveTopLeft(QPoint(w, 0));
        that->d.actionRects[i] = r;
        w += r.width();
        h = qMax(h, r.height());
    }
//    h += 4;
    d.preferredSize = QSizeF( w, h );
    setMinimumSize(w, h);
}

void
MenuBar::wheelEvent(QGraphicsSceneWheelEvent *ev)
{
    ((QEvent*)ev)->ignore();
}

QGraphicsView *
MenuBar::view() const
{
    if (Plasma::Applet *applet = dynamic_cast<Plasma::Applet*>(parentItem()))
        return applet->view();
    return NULL;
}
