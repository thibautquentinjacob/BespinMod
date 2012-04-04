//////////////////////////////////////////////////////////////////////////////
// client.cpp
// -------------------
// Bespin window decoration for KDE
// -------------------
// Copyright (c) 2008/2009 Thomas Luebking <thomas.luebking@web.de>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

// #include <KGlobal>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QTimer>
#include <QVBoxLayout>
#include <QX11Info>
#include <QtDebug>

#include <kdeversion.h>
#include <klocale.h>
#include <kwindowinfo.h>
#include <kwindowsystem.h>
#include <netwm.h>

#include <cmath>

#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <X11/Xatom.h>
#include "../fixx11h.h"

#include "../blib/colors.h"
#include "../blib/FX.h"
#include "../blib/gradients.h"
#include "../blib/xproperty.h"
#include "../blib/shadows.h"
#include "../blib/shapes.h"
#include "button.h"
#include "resizecorner.h"
#include "client.h"

using namespace Bespin;

Client::Client(KDecorationBridge *b, Factory *f) :
KDecoration(b, f), retry(0), myButtonOpacity(0), myActiveChangeTimer(0),
topTile(0), btmTile(0), cornerTile(0), lCorner(0), rCorner(0),
bgMode(Factory::defaultBgMode()), corner(0), bg(0)
{
    setParent( f );
}

Client::~Client()
{
    if (bg)
    {
        if (! --bg->set->clients)
            Factory::kickBgSet(bg->hash);
        delete bg;
    }
//    delete corner;
//    delete [] buttons;
//    delete myTitleBar;
//    delete myTitleSpacer;
}

void
Client::updateStylePixmaps()
{
    topTile = btmTile = cornerTile = lCorner = rCorner = 0;
    unsigned long _5 = 5;
    if (WindowPics *pics = (WindowPics*)XProperty::get<Picture>(windowId(), XProperty::bgPics, XProperty::LONG, &_5))
    {
        if (FX::usesXRender() && (topTile = pics->topTile))
        {
            if (bg)
            {
                if (! --bg->set->clients)
                    Factory::kickBgSet(bg->hash);
                delete bg;
                bg = 0;
            }
            btmTile = pics->btmTile;
            cornerTile = pics->cnrTile;
            lCorner = pics->lCorner;
            rCorner = pics->rCorner;
        }
        else
        {
            qint64 hash = 0;
            /// NOTICE style encodes the intensity in btmTile!
            BgSet *set = Factory::bgSet(colors[isActive()][0], bgMode == 2, pics->btmTile, &hash);
            if (!bg)
            {
                ++set->clients;
                bg = new Bg;
                bg->hash = hash;
                bg->set = set;
            }
            else if (bg->hash != hash)
            {
                if (! --bg->set->clients)
                    Factory::kickBgSet(bg->hash);
                ++set->clients;
                bg->set = set;
                bg->hash = hash;
            }
            if (FX::usesXRender())
            {
                topTile = set->topTile.x11PictureHandle();
                btmTile = set->btmTile.x11PictureHandle();
                cornerTile = set->cornerTile.x11PictureHandle();
                lCorner = set->lCorner.x11PictureHandle();
                rCorner = set->rCorner.x11PictureHandle();
            }
            else
                topTile = btmTile = cornerTile = lCorner = rCorner = -1;
        }
        XFree(pics);
    }
    if (topTile)
        widget()->update();
    else
    {
        if ((!retry || sender()) && retry < 50)
        {
            QTimer::singleShot(100+10*retry, this, SLOT(updateStylePixmaps()));
            ++retry;
        }
    }
}

void
Client::updateUnoHeight()
{
#if 0
    // NOTICE: this should be superflous!
    WindowData *data = (WindowData*)XProperty::get<uint>(windowId(), XProperty::winData, XProperty::WORD, 9);
    if (data)
    {
        unoHeight = ((data->style >> 24) & 0xff);
        widget()->update();
        XFree(data);
    }
#endif
}

void
Client::activeChange()
{
    if (gType[0] != gType[1])
        updateTitleLayout(widget()->size());
    fadeButtons();
    if (bgMode > 1)
        updateStylePixmaps();
#if KDE_IS_VERSION(4,7,0)
    if (Factory::variableShadowSizes())
        Bespin::Shadows::set(windowId(), isActive() ? Bespin::Shadows::Large : Bespin::Shadows::Small, true);
#endif
//     if (unoHeight)
//         updateUnoHeight();
    if (corner)
    {
        corner->setColor(color(ColorTitleBar, isActive()));
        corner->update();
    }
    widget()->update();
}

void
Client::addButtons(const QString& s, int &sz, bool left)
{
    sz = 4;
    if (!s.length() > 0) return;
    Button::Type type;
    for (int n=0; n < s.length(); ++n)
    {
        switch (s[n].toAscii())
        {
        // i'm no way a friend of cluttering your titlebar with buttons =P
        case 'M': // Menu
        case 'S': // Sticky
        case 'H': // Help
        case 'F': // Keep Above
        case 'B': // Keep Below
        case 'L': // Shade button
            if (Factory::multiButtons().isEmpty())
                continue; // no button to insert
            type = Button::Multi; break;
        case 'I': // Minimize
            if (!(isMinimizable() || isMaximizable()))
                continue;
            type = Button::Min; break;
        case 'A': // Maximize
            if (!(isMinimizable() || isMaximizable()))
                continue;
            type = Button::Max; break;
        case 'X': // Close button
            type = Button::Close; break;
        case '_': // Spacer
            myTitleBar->addSpacing(5);
            sz += 7;
        default:
            continue;
        }
        if (!buttons[type])
        {   // will be d'played d'abled in case
            buttons[type] = new Button(this, type, left);
            // optimizes, but breaks with recent KDE/X/nvidia? combinations...
            if (!isPreview())
            {
//                 buttons[type]->setAutoFillBackground(true);
//                 buttons[type]->setAttribute(Qt::WA_OpaquePaintEvent);
//                 buttons[type]->setAttribute(Qt::WA_PaintOnScreen);
                buttons[type]->setAttribute(Qt::WA_NoSystemBackground);
            }
            myTitleBar->addWidget(buttons[type], 0, Qt::AlignCenter);
            sz += (Factory::buttonSize(iAmSmall) + 2);
        }
    }
}

void
Client::borders( int& left, int& right, int& top, int& bottom ) const
{
    // KWin seems to call borders() before maximizeChange() in case
    // this may be a bug but is annoying at least - TODO: kwin bug report?
    int *title, *border, *counter;
    if (Factory::verticalTitle())
    {
        if (isShade())
        {
            top = widget()->height() - 2*myEdgeSize;
            left = Factory::titleSize(iAmSmall) + 8;
            right = Factory::titleSize(iAmSmall) + 8 - widget()->width();
            bottom = 0;
            return;
        }
        title = &left;
        border = &top;
        counter = &right;
    }
    else
        { title = &top; border = &left; counter = &bottom; }

    if (maximizeMode() == MaximizeFull)
    {
        *title = Factory::buttonSize(iAmSmall) + 5;
        if ( options()->moveResizeMaximizedWindows() )
        {
            *border = right = qMin(4, Factory::edgeSize());
            *counter =  qMin(4, Factory::baseSize());
        }
        else
            *border = right = *counter = 0;
    }
    else
    {
        *title = Factory::titleSize(iAmSmall);
        *border = right = Factory::edgeSize();
        *counter = isShade() ? 12 : Factory::baseSize();
    }
}

int
Client::buttonBoxPos(bool active)
{
    if (bgMode == 1 || !gType[active])
        return 0;
    if (buttonSpaceLeft < buttonSpaceRight)
        return 1;
    return -1;
}

void
Client::captionChange()
{
    myCaption = trimm(caption());
    myCaption.replace(i18n("[modified]"), "*");
//     if (Factory::verticalTitle() && buttons[Button::Multi])
//         buttons[Button::Multi]->setToolTip(myCaption);
//     else
        widget()->update();
}

QColor
Client::color(ColorType type, bool active) const
{
    if (type < 4)
        return colors[active][type];
    return options()->color(type, active);
}

bool
Client::eventFilter(QObject *o, QEvent *e)
{
    if (o != widget())
        return false;
    switch (e->type())
    {
    case QEvent::Paint:
    {
        const bool realWindow = !isPreview();
        QRegion clip = static_cast<QPaintEvent*>(e)->region();

#if 0
        QPaintDevice *dev = QPainter::redirected(widget());
        if (dev && dev->devType() == QInternal::Widget)
        qDebug() << static_cast<QWidget*>(dev) << static_cast<QWidget*>(dev)->geometry();
        else if (dev && dev->devType() == QInternal::Pixmap)
        qDebug() << "Pixmap" << static_cast<QPixmap*>(dev)->size();
#endif

        QPainter p(widget());
        p.setClipRegion(clip);
        // WORKAROUND a bug in QPaintEngine + QPainter::setRedirected
        if (dirty[isActive()])
        {
            dirty[isActive()] = false;
            repaint(p, bgMode < 2 && gType[isActive()]);
        }
        repaint(p);

        if ( Factory::roundCorners() && realWindow && maximizeMode() != MaximizeFull && Factory::compositingActive() )
        {
            const bool full = isShade() || myBaseSize > 3;
            const int sw = Factory::mask.width() / 2 + 1;
            const int sh = Factory::mask.height() / 2 + 1;
            const int sx = Factory::mask.width() - sw;
            const int sy = Factory::mask.height() - sh;
            const int x2 = widget()->rect().width() - sw;
            const int y2 = widget()->rect().height() - sh;
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);

            p.drawPixmap( 0,0, Factory::mask, 0,0, sw,sh ); // topLeft
            if ( full || !Factory::verticalTitle() )
                p.drawPixmap( x2,0, Factory::mask, sx,0, sw,sh ); // topRight
            if ( full || Factory::verticalTitle() )
                p.drawPixmap( 0,y2, Factory::mask, 0,sy, sw,sh ); // btmLeft
            if ( full )
                p.drawPixmap( x2,y2, Factory::mask, sx,sy, sw,sh ); // btmRight
        }

        p.end();

        if (realWindow)
        {
            QPixmap *buffer = 0;
            QPixmap dBuffer;
            QPoint off(0,0);

            if (color(ColorTitleBar, isActive()).alpha() == 0xff)
            {
                // try to copy from redirection
                if (FX::usesXRender())
                if ( QPaintDevice *device = QPainter::redirected(widget(), &off) )
                {
                    if (device->devType() == QInternal::Pixmap)
                        buffer = static_cast<QPixmap*>(device);
                }
                if (!buffer)
                {
                    // nope, repaint tp buffer
                    dBuffer = QPixmap(myTitleBar->geometry().size());
                    buffer = &dBuffer;
                    p.begin(buffer);
//                     p.setClipping(false);
                    p.setClipRegion(myTitleBar->geometry());
                    repaint(p, false);
                    p.end();
                }
            }

            for (int i = 0; i < 4; ++i)
                if (buttons[i])
                {   // dump button BGs unless ARGB
                    buttons[i]->setBg(buffer ? buffer->copy(buttons[i]->geometry().translated(-off)) : dBuffer);
                    // enforce repaint, button thinks it's independend
                    buttons[i]->repaint();
                }

            if (corner)
                corner->repaint();
        }
        return true;
    }
    case QEvent::Enter:
    case QEvent::Leave:
        if (!isActive())
            fadeButtons();
        return false;
    case QEvent::MouseButtonDblClick:
        titlebarDblClickOperation();
        return true;
    case QEvent::MouseButtonPress:
        processMousePressEvent(static_cast<QMouseEvent*>(e));
        return true;
    case QEvent::Wheel:
        titlebarMouseWheelOperation(static_cast<QWheelEvent*>(e)->delta());
        return true;
        //       case QEvent::MouseButtonRelease:
    default:
        return false;
    }
    return false;
}


void
Client::fadeButtons()
{
    if (Factory::config()->hideInactiveButtons && !myActiveChangeTimer)
    {
        myActiveChangeTimer = startTimer(40);
        QTimerEvent te(myActiveChangeTimer);
        timerEvent(&te);
    }
}

static const unsigned long
supported_types =   NET::NormalMask | NET::DesktopMask | NET::DockMask | NET::ToolbarMask |
                    NET::MenuMask | NET::DialogMask | NET::OverrideMask | NET::TopMenuMask |
                    NET::UtilityMask | NET::SplashMask;

void
Client::init()
{
    createMainWidget();
#if KDE_IS_VERSION(4,7,0)
    Bespin::Shadows::set(windowId(), Bespin::Shadows::Large, true);
#endif
    dirty[0] = dirty[1] = true;

    KWindowInfo info(windowId(), NET::WMWindowType, NET::WM2WindowClass);
    NET::WindowType type = info.windowType( supported_types );
    iAmSmall = (type == NET::Utility || type == NET::Menu || type == NET::Toolbar) ||
                Factory::config()->smallTitleClasses.contains(info.windowClassName(), Qt::CaseInsensitive) ||
                Factory::config()->smallTitleClasses.contains(info.windowClassClass(), Qt::CaseInsensitive);

    if (isPreview())
        myCaption =  isActive() ? "Active Window" : "Inactive Window";
    else if (!Factory::verticalTitle())
        myCaption = trimm(caption());
    widget()->setAutoFillBackground(!isPreview());
    widget()->setAttribute(Qt::WA_OpaquePaintEvent, !isPreview());
//     widget()->setAttribute(Qt::WA_NoSystemBackground, !isPreview());
    widget()->setAttribute(Qt::WA_PaintOnScreen, !isPreview());
    widget()->setAttribute(Qt::WA_StyledBackground, false);
    widget()->installEventFilter(this);

    QBoxLayout *layout;
    if (Factory::verticalTitle())
    {
        myTitleBar = new QVBoxLayout();
        myTitleBar->setContentsMargins(0,4,0,4);
        layout = new QHBoxLayout(widget());
        myTitleSpacer = new QSpacerItem( myTitleSize, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
    else
    {
        myTitleBar = new QHBoxLayout();
        myTitleBar->setContentsMargins(4,0,4,0);
        layout = new QVBoxLayout(widget());
        myTitleSpacer = new QSpacerItem( 1, myTitleSize, QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
    myTitleBar->setSpacing(2);

    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addLayout(myTitleBar);
    layout->addStretch(1000);

    for (int i = 0; i < 4; ++i)
        buttons[i] = 0;
    gType[0] = Gradients::None;
    gType[1] = Gradients::Button;

    if (!isPreview() && Factory::config()->resizeCorner && isResizable())
        corner = new ResizeCorner(this);
    reset(63);

    if (Factory::verticalTitle())
        captionChange();
}

void
Client::maximizeChange()
{
    reset(SettingBorder);
    emit maximizeChanged(maximizeMode() == MaximizeFull);
}

#define PARTIAL_MOVE 0

KDecorationDefines::Position
Client::mousePosition( const QPoint& p ) const
{
    if (isShade() || !isResizable())
        return PositionCenter;

    if (p.y() < 4)
    {   // top
        if (p.x() < 4) return PositionTopLeft; // corner
        if (p.x() > width() - 4) return PositionTopRight; // corner
        return PositionTop;
    }
    if (p.y() > height() - 16)
    {   // bottom
        if (p.x() < 16) return PositionBottomLeft; // corner
        if (p.x() > width() - 16) return PositionBottomRight; // corner
#if PARTIAL_MOVE
        int off = width()/3;
        if (p.x() > off && p.x() < width() - off) return PositionBottom;
        return PositionCenter; // not on outer 3rds
#else
        return PositionBottom;
#endif
    }
    if (p.x() < 4)
    {   // left
#if PARTIAL_MOVE
        int off = height()/3;
        if (p.y() > off && p.y() < height() - off) return PositionLeft;
        return PositionCenter; // not on outer 3rds
#else
        return PositionLeft;
#endif
    }
    if (p.x() > width() - 4)
    {   // right
#if PARTIAL_MOVE
        int off = height()/3;
        if (p.y() > off && p.y() < height() - off) return PositionRight;
        return PositionCenter; // not on outer 3rds
#else
        return PositionRight;
#endif
    }
    return PositionCenter; // to convince gcc, never reach this anyway
}

QSize
Client::minimumSize() const
{
    if (Factory::verticalTitle())
        return QSize(myTitleSize + myBaseSize, buttonSpaceLeft + buttonSpaceRight + 2*myEdgeSize);
    else
        return QSize(buttonSpaceLeft + buttonSpaceRight + 2*myEdgeSize, myTitleSize + myBaseSize);
}

#define DUMP_PICTURE(_PREF_, _PICT_)\
if (FX::usesXRender()) { \
if (bg.alpha() != 0xff){\
    _PREF_##Buffer.detach();\
    _PREF_##Buffer.fill(Qt::transparent);\
    XRenderComposite(QX11Info::display(), PictOpOver, _PICT_, 0, _PREF_##Buffer.x11PictureHandle(),\
    0, 0, 0, 0, 0, 0, _PREF_##Width, _PREF_##Height);\
}\
else {\
    _PREF_##Buffer.fill(bg);\
    XRenderComposite(QX11Info::display(), PictOpSrc, _PICT_, 0, _PREF_##Buffer.x11PictureHandle(),\
    0, 0, 0, 0, 0, 0, _PREF_##Width, _PREF_##Height);\
}}\
else if (this->bg && this->bg->set) { \
    _PREF_##Buffer = this->bg->set->_PICT_; \
}

inline static void shrink(QFont &fnt, float factor)
{
    if (fnt.pointSize() > -1)
        fnt.setPointSize(qRound(fnt.pointSize()*factor));
    else
        fnt.setPixelSize(qRound(fnt.pixelSize()*factor));
}

void
Client::repaint(QPainter &p, bool paintTitle)
{
    if (!Factory::initialized())
        return;

    QColor bg = color(ColorTitleBar, isActive());

    // preview widget =============================================================================
    if (isPreview())
    {
        QRect r = widget()->rect();
        QRect r2 = QRect( 2, 2, r.width()-2, r.height()-2 );
        bool hadAntiAliasing = p.testRenderHint(QPainter::Antialiasing);
        p.setRenderHint( QPainter::Antialiasing );
        // the shadow - this is rather expensive, but hey - who cares... ;-P
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(0,0,0,40));
        p.drawRoundedRect(r, 8, 8);
        r.adjust(1,0,-1,-1);
        p.drawRoundedRect(r, 7, 7);
        r.adjust(1,0,-1,-1);
        p.setBrush(QColor(0,0,0,20));
        p.drawRoundedRect(r, 6, 6);
        r.adjust(0,0,0,-1);
        p.drawRoundedRect(r, 6, 6);
        r.adjust(0,0,0,-1);

        // the window

        p.setBrush(Gradients::pix(bg, r2.height(), Qt::Vertical, Gradients::Button));
        QColor c = color(Client::ColorFont, isActive());
        c.setAlpha(100);
        p.setPen(c);
        p.drawRoundedRect(r, 6, 6);

        // logo
        if (isActive())
        {
            const int s = qMin(r.width(), r.height())/2;
            QRect logo(0,0,s,s);
            logo.moveCenter(r.center());

            c.setAlpha(180); p.setBrush(c); p.setPen(Qt::NoPen);
            p.drawPath(Shapes::logo(logo));
        }
        c.setAlpha(255); p.setPen(c); p.setBrush(Qt::NoBrush);
        p.drawText(r, Qt::AlignHCenter | Qt::TextSingleLine | Qt::AlignTop, myCaption);
        p.setRenderHint( QPainter::Antialiasing, hadAntiAliasing );
    }

    // only one "big" gradient, as we can't rely on windowId()! ====================================
    else if (isShade())
    {
        const Qt::Orientation o = Factory::verticalTitle() ? Qt::Horizontal : Qt::Vertical;
        const QPixmap &fill = Gradients::pix(bg, width(), o, Gradients::Button);
        p.drawTiledPixmap(0,0,width(),height(), fill);
    }

    // window ===================================================================================
    else
    {
        p.setBrush(bg); p.setPen(Qt::NoPen);
        switch (bgMode)
        {
        case 2: // vertical gradient
        {
#define ctWidth 32
#define ctHeight 128
#define tbWidth 32
#define tbHeight 256
#define lrcWidth 128
#define lrcHeight 128

            if (!topTile)
            {   // hmm? paint fallback
                p.drawRect(left); p.drawRect(right); p.drawRect(top); p.drawRect(bottom);
                // and wait for pixmaps
                updateStylePixmaps();
                break;
            }

            p.drawRect(left); p.drawRect(right);
            if (bg.alpha() != 0xff)
                { p.drawRect(top); p.drawRect(bottom); }

            QPixmap tbBuffer(tbWidth, tbHeight);
            int s1 = tbHeight;
            int s2 = qMin(s1, (height()+1)/2);
            s1 -= s2;
            DUMP_PICTURE(tb, topTile);
            p.drawTiledPixmap( 0, 0, width(), s2, tbBuffer, 0, s1 );
            if (Colors::value(bg) < 245 && bg.alpha() == 0xff)
            {   // makes no sense otherwise
                const int w = width()/4 - 128;
                if (w > 0)
                {
                    s2 = 128-s1;
                    QPixmap ctBuffer(ctWidth, ctHeight);
                    DUMP_PICTURE(ct, cornerTile);
                    p.drawTiledPixmap( 0, 0, w, s2, ctBuffer, 0, s1 );
                    p.drawTiledPixmap( width()-w, 0, w, s2, ctBuffer, 0, s1 );
                }
                QPixmap lrcBuffer(lrcWidth, lrcHeight);
                DUMP_PICTURE(lrc, lCorner);
                p.drawPixmap(w, 0, lrcBuffer, 0, s1, 128, s2);
                DUMP_PICTURE(lrc, rCorner);
                p.drawPixmap(width()-w-128, 0, lrcBuffer, 0, s1, 128, s2);
            }
            if ( !( myBaseSize || Factory::verticalTitle() ) )
                break;
            s1 = tbHeight;
            s2 = qMin(s1, height()/2);
            DUMP_PICTURE(tb, btmTile);
            p.drawTiledPixmap( 0, height()-s2, width(), s2, tbBuffer );
            break;
        }
#undef tbWidth
#undef tbHeight
#undef lrcWidth
#undef lrcHeight

        case 3: // horizontal gradient
        {
#define tbWidth 256
#define tbHeight 32
#define lrcWidth 256
#define lrcHeight 32

            p.drawRect(top); // can be necessary for flat windows
            p.drawRect(bottom);
            if (bg.alpha() != 0xff)
                { p.drawRect(left); p.drawRect(right); }
            int s1 = tbWidth;
            int s2 = qMin(s1, (width()+1)/2);
            const int h = qMin(128+32, height()/8);
            QPixmap tbBuffer(tbWidth, tbHeight);
            QPixmap lrcBuffer(lrcWidth, lrcHeight);
            QPixmap ctBuffer(ctWidth, ctHeight);
            DUMP_PICTURE(tb, topTile); // misleading, this is the LEFT column
            p.drawTiledPixmap( 0, h, s2, height()-h, tbBuffer, s1-s2, 0 );
            DUMP_PICTURE(lrc, lCorner); // left bottom shine
            p.drawPixmap(0, h-32, lrcBuffer, s1-s2, 0,0,0);
            DUMP_PICTURE(tb, btmTile); // misleading, this is the RIGHT column
            p.drawTiledPixmap( width() - s2, h, s2, height()-h, tbBuffer );
            DUMP_PICTURE(lrc, rCorner); // right bottom shine
            p.drawPixmap(width() - s2, h-32, lrcBuffer);
            DUMP_PICTURE(ct, cornerTile); // misleading, TOP TILE
            p.drawTiledPixmap( 0, h-(128+32), width(), 128, ctBuffer );
            break;
        }
        case 0: // plain
            p.setBrush(bg); p.setPen(Qt::NoPen);
            p.drawRect(left); p.drawRect(right);
            p.drawRect(top); p.drawRect(bottom);
            break;
        default:
        case 1: // scanlines, fallback
        {
            const Gradients::Type gradient = (bgMode == 0xff) ? gType[isActive()] : Factory::config()->gradient[0][isActive()];
            Qt::Orientation o = Qt::Vertical;
            QRect ttBar = top;
            QLine borderline;
            if (Factory::verticalTitle())
            {
                o = Qt::Horizontal;
                ttBar = left;
                p.drawRect(top);
                borderline.setLine(myTitleSize-1, myEdgeSize, myTitleSize-1, height()-myEdgeSize);
            }
            else
            {
                p.drawRect(left);
                borderline.setLine(myEdgeSize, myTitleSize-1, width()-myEdgeSize, myTitleSize-1);
            }
            p.drawRect(right); p.drawRect(bottom);
            if (gradient == Gradients::None)
                p.drawRect(ttBar);
            else
            {
                p.fillRect(ttBar, Gradients::brush(bg, myTitleSize, o, gradient));
                p.setPen(Colors::mid(bg, Qt::black,6,1));
                p.drawLine(borderline);
//                 p.setPen(Colors::mid(bg, Qt::white,6,1));
//                 p.drawLine(0,myTitleSize-1,width(),myTitleSize-1);
            }

            if ( bgMode == 0xff )  // no deco gradient in this mode
                break;

            const Gradients::Type titleGradient = gType[isActive()];
            if (paintTitle && titleGradient && label.width())
            {   // nice deco
                p.setRenderHint( QPainter::Antialiasing );
                bg = color(ColorTitleBlend, isActive());
                const QPixmap &fill = Gradients::pix(bg, myTitleSize, o, titleGradient);
//                 p.setPen(Qt::NoPen); p.setBrush(Gradients::structure(bg, true));
                const QColor shadow = Colors::mid(bg, Qt::black,6,1);
                p.setPen(QPen(shadow, 2)); p.setBrush(fill);
                if (Factory::verticalTitle())
                    p.drawRoundRect(label.adjusted(4,0,-4,0),99,myTitleSize*99/label.height());
                else
                    p.drawRoundRect(label.adjusted(0,4,0,-4),myTitleSize*99/label.width(),99);
                p.setRenderHint( QPainter::Antialiasing, false );
            }
            break;
        }
        }
    }

    if (unoHeight && !Factory::verticalTitle())
    {
      const Gradients::Type gradient = gType[isActive()];
      //     My mess
      p.setRenderHint( QPainter::Antialiasing, true );
      p.setPen(QPen(QColor(0,0,0,255), 5));
      p.drawRoundedRect( 0, 0, width(), height(), 8, 8 );
      
      p.setPen(QPen(QColor(242, 242, 242, 255), 1));
      p.drawRoundedRect( 1, 1, width()-2, height()-2, 8, 8 );
      p.setRenderHint( QPainter::Antialiasing, false );
      
      QRect rect2 = QRect( 1, 1, top.width() - 3, top.height() );
      if (gradient != Gradients::None) {
        //            p.fillRect(rect2, Gradients::brush(bg, unoHeight, Qt::Vertical, gradient));
        p.setBrush( Gradients::brush(bg, unoHeight, Qt::Vertical, gradient) );
        p.setPen( QPen( Qt::NoPen ) );              // do not draw outline
        p.drawRoundedRect( rect2, 8, 8 );   // draw filled rectangle
      }
      
    }

    if (paintTitle && isShade())
    {   // splitter
//         QColor bg2 = color(ColorTitleBlend, isActive());
        p.setPen(Colors::mid(bg, Qt::black, 3, 1));
        int xy = myTitleSize-2;
        if (Factory::verticalTitle())
        {
            p.drawLine(xy, 8, xy, height()-8);
            ++xy;
            p.setPen(Colors::mid(bg, Qt::white, 2, 1));
            p.drawLine(xy, 8, xy, height()-8);
        }
        else
        {
            p.drawLine(8, xy, width()-8, xy);
            ++xy;
            p.setPen(Colors::mid(bg, Qt::white, 2, 1));
            p.drawLine(8, xy, width()-8, xy);
        }
    }

//     paintTitle = paintTitle && !Factory::verticalTitle();
    const int sz = Factory::verticalTitle() ? label.height() : label.width();
    // title ==============
    if (paintTitle && sz > 0)
    {
        const QColor titleColor = color((isShade() && bgMode == 1) ? ColorButtonBg : ColorFont, isActive());
        int tf = Factory::config()->titleAlign | Qt::AlignVCenter | Qt::TextSingleLine;

        // FONT ==========================================
        QFont fnt = options()->font();
        if (iAmSmall) {
            shrink(fnt, Factory::smallFactor());
            tf |= Qt::AlignBottom;
        }
        else
            tf |= Qt::AlignVCenter;
        float tw = 1.07*QFontMetrics(fnt).size(tf, myCaption).width();
        if (tw > sz)
        {
            float f = sz/tw;
            if (f > 0.9)
                fnt.setStretch(qRound(fnt.stretch()*f));
            else
                shrink(fnt, qMax(f,0.75f));
        }
        p.setFont(fnt);
        // ===============
        if ( Factory::verticalTitle() )
        {
            p.translate(label.center());
            p.rotate(-90.0);
            p.translate(-label.center());
            const int d = (label.height() - label.width()) / 2;
            label.setRect( label.x() - d, label.y() + d, label.height(), label.width() );
        }

        if (bgMode == 1)
            label.adjust(8,0,-8,0);
        if (isActive())
        {
            // emboss?!
            int d = 0;
            const int bgv = Colors::value(bg), fgv = Colors::value(titleColor);
            if (bgv < fgv) // dark bg -> dark top borderline
                { p.setPen(Colors::mid(bg, Qt::black, bgv, 160)); d = -1; }
            else // bright bg -> bright bottom borderline
                { p.setPen(Colors::mid(bg, Qt::white, 16, bgv)); d = 1; }

            QRect tr;
            QPoint off(0,0); Factory::verticalTitle() ? off.setX(-d) : off.setY(d);
            p.drawText ( label.translated(off), tf, myCaption, &tr );

            if ( !(Factory::config()->hideInactiveButtons || Factory::verticalTitle()) )
            {
                if ( (tr.left() - 37 > label.left() && tr.right() + 37 < label.right() ) &&
                    maximizeMode() != MaximizeFull && color(ColorTitleBar, 0) == color(ColorTitleBar, 1) &&
                    gType[0] == gType[1] && color(ColorTitleBlend, 0) == color(ColorTitleBlend, 1) )
                {   // inactive window looks like active one...
                    int y = label.center().y();
                    if ( !(tf & Qt::AlignLeft) )
                        p.drawPixmap(tr.x() - 38, y, Gradients::borderline(titleColor, Gradients::Left));
                    if ( !(tf & Qt::AlignRight) )
                        p.drawPixmap(tr.right() + 6, y, Gradients::borderline(titleColor, Gradients::Right));
                }
            }
        }

        p.setPen(titleColor);
        p.drawText ( label, tf, myCaption );
        if (bgMode == 1)
            label.adjust(-8,0,8,0);
        if ( Factory::verticalTitle() )
        {
            p.translate(label.center());
            p.rotate(90.0);
            p.translate(-label.center());
            const int d = (label.width() - label.height()) / 2;
            label.setRect( label.x() + d, label.y() - d, label.height(), label.width() );
        }

    }

    // bar =========================
    if (!(unoHeight || bgMode == 1 || bgMode == 0xff))
    {
        const QColor bg2 = color(ColorTitleBlend, isActive());

        if (gType[isActive()])
        {   // button corner
            QColor shadow = Colors::mid(bg2, Qt::black,4,1);
            p.setPen(shadow);
#if 0
//             QPaintDevice *dev = p.device();
//             p.end();
            QImage img(32,32, QImage::Format_RGB32); // using ARGB32 fixes it
            QPainter p2(&img);
            p2.setPen(Qt::NoPen);
            p2.setBrush(QColor(255,0,0,255));
            p2.drawRect(img.rect());
            p2.end();
            QPixmap pix = QPixmap::fromImage(img);
//             p.begin(dev);
            p.setBrush(pix);
#else
            const QPixmap &fill = Gradients::pix(bg2, myTitleSize,
                                                 Factory::verticalTitle() ? Qt::Horizontal : Qt::Vertical,
                                                 gType[isActive()]);
            p.setBrush(fill);
#endif
            p.setRenderHint( QPainter::Antialiasing );
            p.drawPath(buttonCorner);
        }

        if ((bg2 != bg) && (myBaseSize > 2 || myEdgeSize > 2 || gType[isActive()]))
        {   // outline
            p.setBrush(Qt::NoBrush);
            p.setRenderHint( QPainter::Antialiasing );
            p.setPen(QPen(bg2,3));
            if ( myBaseSize > 2 )
            {
                if ( myEdgeSize > 2 )
                    p.drawRect(1,1,width()-2,height()-2);
                else if (Factory::verticalTitle())
                {
                    p.drawLine(1,0,1,height());
                    p.drawLine(width()-2,0,width()-2,height());
                }
                else
                {
                    p.drawLine(0,1,width(),1);
                    p.drawLine(0,height()-2,width(),height()-2);
                }
            }
            else if (Factory::verticalTitle())
                p.drawLine(1,0,1,height());
            else
                p.drawLine(0,1,width(),1);
        }
        else if (myBaseSize && myEdgeSize)
        {   // static bool KWindowSystem::compositingActive();
            // frame ==============
            QPainterPath path;
            int x,y,w,h;
            widget()->rect().getRect(&x,&y,&w,&h);
            const int cornerSize = 13;
            path.arcMoveTo(x, y, cornerSize, cornerSize, 90);
            path.arcTo(x, y, cornerSize, cornerSize, 90, 90);
            path.arcTo(x, y+h-cornerSize, cornerSize, cornerSize, 2*90, 90);
            path.arcTo(x+w-cornerSize, y+h-cornerSize, cornerSize, cornerSize, 3*90, 90);
            path.arcTo(x+w-cornerSize, y, cornerSize, cornerSize, 0, 90);
            path.closeSubpath();

            p.setRenderHint( QPainter::Antialiasing, true );
            p.setBrush(Qt::NoBrush);
            int v = Colors::value(bg);
            p.setPen(QPen(Colors::mid(bg,Qt::white,300-v,v),3));
            p.drawPath(path);

            p.setPen(Colors::mid(bg, color(ColorFont, true),5,2));
            p.drawPath(path);
        }
    }
    p.setPen(QColor(255,0,0,255));
    p.drawLine( 0, height() - 30, width(), height() - 30 );
    
}

void
Client::reset(unsigned long changed)
{
    if (changed & SettingFont)
        myTitleSize = Factory::titleSize(iAmSmall);

    if (changed & SettingDecoration)
    {
        gType[0] = Factory::config()->gradient[1][0];
        gType[1] = Factory::config()->gradient[1][1];
        changed |= SettingColors;
    }

    if (changed & SettingBorder)
    {
        if (maximizeMode() == MaximizeFull)
        {
            if (options()->moveResizeMaximizedWindows())
            {
                myBaseSize = qMin(4, Factory::baseSize());
                myEdgeSize = qMin(4, Factory::edgeSize());
            }
            else
            {
                myBaseSize = myEdgeSize = 0;
                if (corner)
                    corner->hide();
            }
            myTitleSize = Factory::buttonSize(iAmSmall) + 5;
        }
        else
        {
            myBaseSize = Factory::baseSize();
            myEdgeSize = Factory::edgeSize();
            myTitleSize = Factory::titleSize(iAmSmall);
            if (corner)
                corner->show();
        }

        if (Factory::verticalTitle())
        {
            const int sideHeight = height() - (myTitleSize + myEdgeSize);
            top.setRect(0, 0, width(), myEdgeSize);
            left.setRect(0, myEdgeSize, myTitleSize, sideHeight);
            right.setRect(0, myEdgeSize, myBaseSize, sideHeight);
            bottom.setRect(0, height()-myEdgeSize, width(), myEdgeSize);
        }
        else
        {
            const int sideHeight = height() - (myTitleSize + myBaseSize);
            top.setRect(0, 0, width(), myTitleSize);
            left.setRect(0, myTitleSize, myEdgeSize, sideHeight);
            right.setRect(width()-myEdgeSize, myTitleSize, myEdgeSize, sideHeight);
            bottom.setRect(0, height()-myBaseSize, width(), myBaseSize);
        }

        uint decoDim = ((left.width() & 0xff) << 24) | ((top.height() & 0xff) << 16) | ((right.width() & 0xff) << 8) | (bottom.height() & 0xff);
        XProperty::set<uint>(windowId(), XProperty::decoDim, &decoDim, XProperty::LONG);

        changed |= SettingFont;
    }

    if (changed & SettingFont)
    {
        if (Factory::verticalTitle())
            myTitleSpacer->changeSize( myTitleSize, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
        else
            myTitleSpacer->changeSize( 1, myTitleSize, QSizePolicy::Expanding, QSizePolicy::Fixed);
        myTitleBar->invalidate();
    }

    if (changed & SettingButtons)
    {
        myButtonOpacity = (isActive() || !Factory::config()->hideInactiveButtons) ? 100 : 0;
        QLayoutItem *item;
        while ((item = myTitleBar->takeAt(0)))
            if (item != myTitleSpacer) {
                if (item->widget())
                    delete item->widget();
                else if (item->spacerItem())
                    delete item->spacerItem();
                else
                    delete item;
            }
        for (int i = 0; i < 4; ++i)
            buttons[i] = 0;
        addButtons(options()->titleButtonsLeft(), buttonSpaceLeft, true);
        myTitleBar->addItem(myTitleSpacer);
        addButtons(options()->titleButtonsRight(), buttonSpaceRight, false);
        buttonSpace = qMax(buttonSpaceLeft, buttonSpaceRight);
    }

    if ((changed & (SettingButtons | SettingFont)) && (buttonSpaceLeft >= buttonSpaceRight))
        updateButtonCorner(false);

    if (changed & SettingColors)
    {   // colors =====================
        for (int a = 0; a < 2; ++a)
        for (int t = 0; t < 4; ++t)
            colors[a][t] = options()->color((ColorType)t, a);

        bool def = true;
        if (isPreview())
        {
            def = false;
            bgMode = 0;
            gType[0] = gType[1] = Gradients::None;

            colors[0][ColorTitleBlend] = colors[1][ColorTitleBlend] =
            colors[0][ColorTitleBar] = colors[1][ColorTitleBar] =
            widget()->palette().color(QPalette::Active, QPalette::Window);

            colors[1][ColorButtonBg] = colors[1][ColorFont] =
            widget()->palette().color(QPalette::Active, QPalette::WindowText);

            colors[0][ColorButtonBg] = colors[0][ColorFont] =
            Colors::mid(colors[0][ColorTitleBar], colors[1][ColorFont]);
        }
        else if (!Factory::config()->forceUserColors)
        {
            unsigned long _9 = 9;
            WindowData *data = 0;
            bool needFree = false;

             // check for data from preset ====================================================
            KWindowInfo info(windowId(), NET::WMWindowType, NET::WM2WindowClass);
            data = Factory::decoInfo(info.windowClassClass(), info.windowType(supported_types));
            if (data && (((data->style >> 16) & 0xff) > 1))
            {
                WindowPics pics;
                pics.topTile = pics.cnrTile = pics.lCorner = pics.rCorner = 0;
                /// NOTICE encoding the bg gradient intensity in the btmTile Pic!!
                pics.btmTile = 150;
                XProperty::set<Picture>(windowId(), XProperty::bgPics, (Picture*)&pics, XProperty::LONG, 5);
            }

            // check for data from style ====================================================
            if (!data) {
                data = (WindowData*)XProperty::get<uint>(windowId(), XProperty::winData, XProperty::WORD, &_9);
                if (data)
                    needFree = true;  // X provides a deep copy
            }

            // check for data from dbus =========================================================
            if (!data)
            {
                long int *pid = XProperty::get<long int>(windowId(), XProperty::pid, XProperty::LONG);
                if (pid)
                {
                    if ((data = Factory::decoInfo(*pid)))
                        XProperty::set<uint>(windowId(), XProperty::winData, (uint*)data, XProperty::WORD, 9);
                    XFree(pid);
                }
            }

            // read data ========================================================================
            if (data)
            {
                def = false;
                colors[0][ColorTitleBar].setRgba(data->inactiveWindow);
                colors[1][ColorTitleBar].setRgba(data->activeWindow);
                colors[0][ColorTitleBlend].setRgba(data->inactiveDeco);
                colors[1][ColorTitleBlend].setRgba(data->activeDeco);
                colors[0][ColorFont].setRgba(data->inactiveText);
                colors[1][ColorFont].setRgba(data->activeText);
                colors[0][ColorButtonBg].setRgba(data->inactiveButton);
                colors[1][ColorButtonBg].setRgba(data->activeButton);
                bgMode = ((data->style >> 16) & 0xff);
                unoHeight = ((data->style >> 24) & 0xff); // if (..)
//                     QTimer::singleShot(2500, this, SLOT(updateUnoHeight()));
                gType[0] = (Gradients::Type)((data->style >> 8) & 0xff);
                gType[1] = (Gradients::Type)(data->style & 0xff);
            }

            // free X11 data ======================================================================
            if (needFree)
                XFree(data);
        }

        if (def)
        {   // the fallback solution
            unoHeight = 0;
            if ((bgMode = Factory::defaultBgMode()) > 1)
            {
                WindowPics pics;
                pics.topTile = pics.cnrTile = pics.lCorner = pics.rCorner = 0;
                /// NOTICE encoding the bg gradient intensity in the btmTile Pic!!
                pics.btmTile = 150;
                XProperty::set<Picture>(windowId(), XProperty::bgPics, (Picture*)&pics, XProperty::LONG, 5);
            }
            for (int i = 0; i <  2; ++i)
            {
                if (!gType[i])
                {   //buttoncolor MUST be = titlefont
                    colors[i][ColorTitleBlend] = colors[i][ColorTitleBar];
                    colors[i][ColorButtonBg] = colors[i][ColorFont];
                }
#if 0
                // NOTICE this makes no more sense at all since we provide our own coloring... =S
                // usually the window is titlebar colored and the titleblend gradient painted upon - in case
                // but the fallback shall be fully titleblend with a titlebar color section behind the title
                // to not have to handle this during the painting, we just swap the colors here
                else if ( bgMode == 1 )
                {
                    QColor h = colors[i][ColorTitleBlend];
                    colors[i][ColorTitleBlend] = colors[i][ColorTitleBar];
                    colors[i][ColorTitleBar] = h;
                }
#endif
            }
        }
        else if (bgMode == 1)
        {
            // iff the user set a colormode from the style, but no gradient, we use the color on
            // the default gradient and NOT the nonexisting accessoire
            for (int i = 0; i <  2; ++i)
            {
                if (gType[i] == Gradients::None)
                {
                    colors[i][ColorTitleBar] = colors[i][ColorTitleBlend];
                    colors[i][ColorFont] = colors[i][ColorButtonBg];
                }
                else
                {   // needs titlefont and button bg swapped...
                    QColor h = colors[i][ColorButtonBg];
                    colors[i][ColorButtonBg] = colors[i][ColorFont];
                    colors[i][ColorFont] = h;
                }
            }
            // last, clamp ColorTitleBlend to v >= 80
            int h,s,v;
            for (int i = 0; i <  2; ++i)
            {
                v = Colors::value(colors[i][ColorTitleBlend]);
                if (v < 70)
                {
                    colors[i][ColorTitleBlend].getHsv(&h,&s,&v);
                    colors[i][ColorTitleBlend].setHsv(h,s,70);
                }
            }
        }
        QPalette pal = widget()->palette();
        pal.setColor(QPalette::Active, widget()->backgroundRole(), color(ColorTitleBar, true));
        pal.setColor(QPalette::Inactive, widget()->backgroundRole(), color(ColorTitleBar, false));
        pal.setColor(QPalette::Disabled, widget()->backgroundRole(), color(ColorTitleBar, false));
        widget()->setPalette(pal);
    }

    // WORKAROUND a bug apparently in QPaintEngine which seems to
    // fail to paint IMAGE_RGB -> QPixmap -> device while device is redirected
    dirty[0] = dirty[1] = color(ColorTitleBar, isActive()).alpha() == 0xff;
    if (changed)
        activeChange(); // handles bg pixmaps in case and triggers update

}

void
Client::updateButtonCorner(bool right)
{
    const int ts = myTitleSize;
    if (Factory::verticalTitle())
    {
        if (right) // bottom
        {
            const int h = height();
            const int dr = buttonSpaceRight + myTitleSize;
            const int bs = buttonSpaceRight;
            buttonCorner = QPainterPath(QPoint(-1, h));
            buttonCorner.lineTo(ts, h);
            buttonCorner.lineTo(ts, h - bs + ts/2); // straight to bl offset
            buttonCorner.cubicTo(ts+2, h - dr + ts/2,  0, h-bs,  -1, h-dr); // curve to tr offset
        }
        else
        {
            const int dl = buttonSpaceLeft + myTitleSize;
            const int bs = buttonSpaceLeft;
            buttonCorner = QPainterPath(QPoint(-1, 0)); //tl corner
            buttonCorner.lineTo(-1, dl); // straight to tl end
            buttonCorner.cubicTo(0, bs,  ts+2, dl - myTitleSize/2,  ts, bs - ts/2); // curve to bl offset
            buttonCorner.lineTo(ts, 0); // straight to bl end
        }
    }
    else if (right)
    {
        const int w = width();
        const int dr = buttonSpaceRight + myTitleSize;
        const int bs = buttonSpaceRight;
        buttonCorner = QPainterPath(QPoint(w, -1)); //tl corner
        buttonCorner.lineTo(w, ts); // straight to br corner
        buttonCorner.lineTo(w - bs + ts/2, ts); // straight to bl offset
        buttonCorner.cubicTo(w - dr + ts/2, ts+2,   w-bs, 0,   w-dr, -1); // curve to tr offset
    }
    else
    {
        const int dl = buttonSpaceLeft + myTitleSize;
        const int bs = buttonSpaceLeft;
        buttonCorner = QPainterPath(QPoint(0, -1)); //tl corner
        buttonCorner.lineTo(dl, -1); // straight to tl end
        buttonCorner.cubicTo(bs, 0,   dl - myTitleSize/2, ts+2,   bs - ts/2, ts); // curve to bl offset
        buttonCorner.lineTo(0, ts); // straight to bl end
    }
}


void
Client::updateTitleLayout( const QSize& )
{
    int dl = buttonSpaceLeft, dr = buttonSpaceRight;
    if (Factory::config()->titleAlign == Qt::AlignHCenter)
        dl = dr = buttonSpace;
    if (bgMode != 1 && (gType[0] || gType[1]))
    {
        if (buttonSpaceLeft <= buttonSpaceRight)
        {
            updateButtonCorner(true);
            dr += myTitleSize;
        }
        else
            dl += myTitleSize;

    }
    else
        { dl += 8; dr += 8; }

    if (Factory::verticalTitle())
        label.setRect(0, dl, myTitleSize, height()-(dl+dr));
    else
        label.setRect(dl, 0, width()-(dl+dr), myTitleSize);

    if (!label.isValid())
        label = QRect();
}

void
Client::resize( const QSize& s )
{
    widget()->resize(s);
    int w = s.width(), h = s.height();

    updateTitleLayout( s );

    top.setWidth( w );
    left.setHeight( h - (top.height() + bottom.height()) );
    bottom.setWidth( w );
    bottom.moveBottom( h-1 );
    right.setHeight( h - (top.height() + bottom.height()) );
    right.moveRight( w-1 );
#if KDE_IS_VERSION(4,7,0)
    if ( Factory::roundCorners() && !Factory::compositingActive() )
#else
    if ( Factory::roundCorners() )
#endif
    {
        if (maximizeMode() == MaximizeFull)
            { clearMask(); widget()->update(); return; }

        int d = (isShade() || myBaseSize > 3) ? 8 : 4;
        QRegion mask;
        if (Factory::verticalTitle())
        {
            mask = QRegion(0, 4, w, h-8);
            mask += QRegion(4, 0, w-d, h);
            mask += QRegion(1, 2, w-d/4, h-4);
            mask += QRegion(2, 1, w-d/2, h-2);
        }
        else
        {
            mask = QRegion(4, 0, w-8, h);
            mask += QRegion(0, 4, w, h-d);
            mask += QRegion(2, 1, w-4, h-d/4);
            mask += QRegion(1, 2, w-2, h-d/2);
        }
        setMask(mask);
    }
    else
        clearMask();

    widget()->update(); // force! there're painting errors otherwise
}

void
Client::setFullscreen(bool on)
{
    unsigned long state = KWindowInfo(windowId(), 0, NET::WMState).state();
    if (on)
        state |= NET::FullScreen;
    else
        state &= ~NET::FullScreen;
    KWindowSystem::setState(windowId(), state);
}

void
Client::shadeChange()
{
    emit shadeChanged(isSetShade());
}

void
Client::showDesktopMenu(const QPoint &p)
{
   QPoint ip = p;
   QPoint gp = widget()->mapToGlobal(QPoint(width()-60, 0));
   if (ip.x() > gp.x()) ip.setX(gp.x());
   Factory::showDesktopMenu(ip, this);
}

void
Client::showWindowList(const QPoint &p)
{
    QPoint ip = p;
    QPoint gp = widget()->mapToGlobal(QPoint(width()-200, 0));
    if (ip.x() > gp.x())
        ip.setX(gp.x());
    Factory::showWindowList(ip, this);
}

void
Client::showInfo(const QPoint &p)
{
    QPoint ip = p;
    QPoint gp = widget()->mapToGlobal(QPoint(width()-320, 0));
    if (ip.x() > gp.x())
        ip.setX(gp.x());
    Factory::showInfo(ip, windowId());
}

void
Client::showWindowMenu(const QRect &r)
{
    showWindowMenu(r.bottomLeft());
}

void
Client::showWindowMenu(const QPoint &p)
{
    QPoint ip = p;
    QPoint gp = widget()->mapToGlobal(QPoint(width()-200, 0));
    if (ip.x() > gp.x())
        ip.setX(gp.x());
    KDecoration::showWindowMenu(ip);
}

void
Client::tileWindow(bool more, bool vertical, bool mirrorGravity)
{
    const int tiles = 6;
    int state = 0, sz = 0, flags = (mirrorGravity ? 3 : 1) | (1<<14);
    bool change = false;
    MaximizeMode mode;
    /*
    The low byte of data.l[0] contains the gravity to use; it may contain any value allowed
    for the WM_SIZE_HINTS.win_gravity property: NorthWest (1), North (2), NorthEast (3),
        West (4), Center (5), East (6), SouthWest (7), South (8), SouthEast (9) and Static (10).
        A gravity of 0 indicates that the Window Manager should use the gravity specified in
        WM_SIZE_HINTS.win_gravity. The bits 8 to 11 indicate the presence of x, y, width and height.
        The bits 12 to 15 indicate the source (see the section called Source indication in requests),
        so 0001 indicates the application and 0010 indicates a Pager or a Taskbar.
        The remaining bits should be set to zero.
        */

    if (vertical)
    {
        if (!(sz = KWindowSystem::workArea().height()))
            return;
        state = lround((double)tiles*height()/sz);
        change = (qAbs(height()-state*sz/tiles) < 0.05*sz);
        flags |= 1<<11;
        mode = MaximizeVertical;
    }
    else
    {
        if (!(sz = KWindowSystem::workArea().width()))
            return;
        state = lround((double)tiles*width()/sz);
        change = (qAbs(width()-state*sz/tiles) < 0.05*sz);
        flags |= 1<<10;
        mode = MaximizeHorizontal;
    }

    if (change)
    {
        if (!more)
            ++state;
        else if (state > 1)
            --state;
    }

    if (!state)
        return;
    if (state == tiles)
    {
        maximize(mode);
        return;
    }

    sz = state*sz/tiles;

    NETRootInfo rootinfo(QX11Info::display(), NET::WMMoveResize );
    rootinfo.moveResizeWindowRequest(windowId(), flags, 0, 0, sz - (left.width()+right.width()), sz - (top.height() + bottom.height()));
}


void
Client::timerEvent(QTimerEvent *te)
{
    if (te->timerId() != myActiveChangeTimer)
    {
        KDecoration::timerEvent(te);
        return;
    }
    if (isActive() || widget()->underMouse())
    {
        myButtonOpacity += 25;
        if (myButtonOpacity > 99)
        {
            killTimer(myActiveChangeTimer);
            myActiveChangeTimer = 0;
            myButtonOpacity = 100;
        }
    }
    else
    {
        myButtonOpacity -= 10;
        if (myButtonOpacity < 1)
        {
            killTimer(myActiveChangeTimer);
            myActiveChangeTimer = 0;
            myButtonOpacity = 0;
        }
    }
    for (int i = 0; i < 4; ++i)
        if (buttons[i])
            buttons[i]->repaint();
}

void
Client::activate()
{
    QAction *act = qobject_cast<QAction*>(sender());
    if (!act)
        return;

    bool ok;
    int id = act->data().toUInt(&ok);
    if (ok)
    {
        KWindowSystem::activateWindow( id );
        return;
    }
    KWindowSystem::activateWindow( windowId() );
}

void
Client::throwOnDesktop()
{
    QAction *act = qobject_cast<QAction*>(sender());
    if (!act)
        return;

    bool ok;
    int desktop = act->data().toInt(&ok);
    if (ok)
        setDesktop(desktop);
}


void
Client::toggleOnAllDesktops()
{
    KDecoration::toggleOnAllDesktops();
    emit stickyChanged(isOnAllDesktops());
}

static bool
isBrowser(const QString &s)
{
    return  !s.compare("konqueror", Qt::CaseInsensitive) ||
            !s.compare("opera", Qt::CaseInsensitive) ||
            !s.compare("arora", Qt::CaseInsensitive) ||
            !s.compare("firefox", Qt::CaseInsensitive) ||
            !s.compare("rekonq", Qt::CaseInsensitive) ||
            !s.compare("leechcraft", Qt::CaseInsensitive) ||
            !s.compare("mozilla", Qt::CaseInsensitive) ||
            !s.compare("chrome", Qt::CaseInsensitive) ||
            !s.compare("safari", Qt::CaseInsensitive); // just in case ;)
}

QString
Client::trimm(const QString &string)
{
    if (!Factory::config()->trimmCaption)
        return string;

    KWindowInfo info(windowId(), 0, NET::WM2WindowClass);
    QString appName(info.windowClassName());

    if (!appName.compare("amarok", Qt::CaseInsensitive))
        return "Amarok";

    const QString kwin_sep = QString(" %1 ").arg(QChar(0x2013));

    /* Ok, *some* apps have really long and nasty window captions
    this looks clutterd, so we allow to crop them a bit and remove
    considered to be uninteresting informations ==================== */

    QString ret = string;

    /* 1st off: we assume the part beyond the last dash (if any) to be the
    uninteresting one (usually it's the apps name, if there's add info, that's
    more important to the user) ------------------------------------- */

    // Amarok 2 is however different...
//     if (ret.contains(" :: "))
//         ret = ret.section(" :: ", 0, -2, QString::SectionSkipEmpty );

    // ok, here's currently some conflict
    // in e.g. amarok, i'd like to snip "amarok" and preserve "<song> by <artist>"
    // but for e.g. k3b, i'd like to get rid of stupid
    // "the kde application to burn cds and dvds" ...
    /*else*/ if (ret.contains(" - "))
        ret = ret.section(" - ", 0, -2, QString::SectionSkipEmpty );
    else if (ret.contains(kwin_sep)) // newer kwin versions use this uf8 dash (stupid idea?)
        ret = ret.section(kwin_sep, 0, -2, QString::SectionSkipEmpty );

    /* Browsers set the title to <html><title/></html> - appname
    Now the page titles can be ridiculously looooong, especially on news
    pages --------------------------------- */
    if (isBrowser(appName))
    {
        int n = qMin(2, ret.count(" - "));
        if (n--) // select last two if 3 or more sects, prelast otherwise
            ret = ret.section(" - ", -2, n-2, QString::SectionSkipEmpty);
    }

    /* next, if there're details, cut of by ": ",
    we remove the general part as well ------------------------------*/
    if (ret.contains(": "))
        ret = ret.section(": ", 1, -1, QString::SectionSkipEmpty );

    /* if this is a url, please get rid of http:// and /file.html ------- */
    if (ret.contains("http://"))
        ret = ret.remove("http://", Qt::CaseInsensitive)/*.section()*/;

    /* last: if the remaining string still contains the app name, please shape
    away additional info like compile time, version numbers etc. ------------ */
    else
    {   // TODO maybe check with regexp and word bounds?

        QRegExp rgxp( "\\b" + appName + "\\b" );
        rgxp.setCaseSensitivity(Qt::CaseInsensitive);
        int i = ret.indexOf( rgxp );
        if (i > -1)
            ret = ret.mid(i, appName.length());
        else
        {
            appName = info.windowClassClass();
            rgxp.setPattern( "\\b" + appName + "\\b" );
            i = ret.indexOf( rgxp );
            if (i > -1)
                ret = ret.mid(i, appName.length());
        }
    }

    // in general, remove leading and ending blanks...
    ret = ret.trimmed();

    if (ret.isEmpty())
        ret = string; // ...

    return ret;

//    KWindowInfo info(windowId(), NET::WMVisibleName | NET::WMName, NET::WM2WindowClass);
//    qDebug() << "BESPIN:" << info.windowClassClass() <<  << info.name() << info.visibleName();
//    QByteArray windowClassClass() const;
//    QByteArray windowClassName() const;
//    QString visibleName() const;
}
