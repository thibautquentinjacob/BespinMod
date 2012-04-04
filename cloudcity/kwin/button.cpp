//////////////////////////////////////////////////////////////////////////////
// button.cpp
// -------------------
// Bespin window decoration for KDE
// -------------------
// Copyright (c) 2008/2009 Thomas Lübking <baghira-style@web.de>
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

#include <QPainter>
#include <QX11Info>
#include <netwm.h>
#include <cmath>

#include "../blib/colors.h"
#include "../blib/FX.h"
#include "../blib/shapes.h"
#include "client.h"
#include "factory.h"
#include "button.h"

using namespace Bespin;

QPainterPath Button::shape[NumTypes];
bool Button::fixedColors = false;

Button::Button(Client *parent, Type type, bool left) : QWidget(parent->widget()),
client(parent), state(0), multiIdx(0), hoverTimer(0), hoverLevel(0)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_Hover, true);

    const int sz = Factory::buttonSize(parent->isSmall());
    setFixedSize(sz, sz);
    setCursor(Qt::ArrowCursor);
    this->left = left;

    myType = type;
    
    if ( (iAmScrollable = ( myType == Multi )) )
    {
        myType = Factory::multiButtons().at(0);
        connect(client, SIGNAL(keepAboveChanged(bool)), SLOT(clientStateChanged(bool)));
        connect(client, SIGNAL(keepBelowChanged(bool)), SLOT(clientStateChanged(bool)));
        connect(client, SIGNAL(stickyChanged(bool)), SLOT(clientStateChanged(bool)));
        connect(client, SIGNAL(shadeChanged(bool)), SLOT(clientStateChanged(bool)));
        if ( Factory::multiButtons().contains( Button::Max ) )
            connect(client, SIGNAL(maximizeChanged(bool)), SLOT(maximizeChanged(bool)) );
        clientStateChanged(false);
    }
    else if ( myType == Max )
        connect(client, SIGNAL(maximizeChanged(bool)), SLOT(maximizeChanged(bool)) );

// 	setToolTip(tip);
}

void
Button::clientStateChanged(bool state)
{
    if (state)
    {
        switch (myType)
        {
        case Above:
        case Below:
            myType = UnAboveBelow; break;
        case Stick:
            myType = Unstick; break;
        case Shade:
            myType = Unshade; break;
        default:
            return;
        }
    }
    else {
        switch (myType)
        {
        case UnAboveBelow:
            myType = Factory::multiButtons().at(multiIdx); break;
        case Unstick:
            myType = Stick; break;
        case Unshade:
            myType = Shade; break;
        default:
            return;
        }
    }
    repaint();
}

bool
Button::isEnabled() const
{
    if (!QWidget::isEnabled())
        return false;
    switch (myType)
    {
        case Close: return client->isCloseable();
        case Min: return client->isMinimizable();
        case Max: return client->isMaximizable();
        default: break;
    }
    return true;
}

void
Button::init(bool leftMenu, bool fColors, int variant)
{
    const int sz = 99;
    fixedColors = fColors;
    for (int t = 0; t < NumTypes; ++t)
        shape[t] = QPainterPath();

    Shapes::Style style = (Shapes::Style)qMin(qMax(0,variant),3);
    
    QRectF bound(-sz/2.0, -sz/2.0, sz, sz);
    shape[Close] = Shapes::close(bound, style);
    shape[Min] = Shapes::min(bound, style);
    shape[Max] = Shapes::max(bound, style);
    shape[Restore] = Shapes::restore(bound, style);
    shape[Stick] = Shapes::stick(bound, style);
    shape[Unstick] = Shapes::unstick(bound, style);
    shape[Above] = Shapes::keepAbove(bound, style);
    shape[Below] = Shapes::keepBelow(bound, style);
    shape[UnAboveBelow] = Shapes::unAboveBelow(bound, style);
    shape[Menu] = Shapes::menu(bound, leftMenu, style);
    shape[Help] = Shapes::help(bound, style);
    shape[Shade] = Shapes::shade(bound, style);
    shape[Unshade] = Shapes::unshade(bound, style);
    shape[Exposee] = Shapes::exposee(bound, style);
    shape[Info] = Shapes::info(bound, style);
#if 0
    tip[Close] = i18n("Close");
    tip[Min] = i18n("Minimize");
    tip[Max] = i18n("Maximize");
    tip[Restore] = i18n("Restore");
    tip[Menu] = i18n("Menu");
    tip[Help] = i18n("Help");
    tip[Above] = i18n("Keep above others");
    tip[Below] = i18n("Keep below others");
    tip[UnAboveBelow] = i18n("Equal to others");
    tip[Stick] = i18n("All Desktops");
    tip[Unstick] = i18n("This Desktops only");
#endif
}

void
Button::enterEvent(QEvent *)
{
    if (!isEnabled())
        return;

    state |= Hovered; hoverOut = false;
    hoverLevel += 2;
    if (hoverLevel > 6)
    {
        hoverLevel = 6;
        if (hoverTimer)
            killTimer(hoverTimer);
        hoverTimer = 0;
        return;
    }
    repaint();
    if (!hoverTimer)
        hoverTimer = startTimer ( 50 );
}

void
Button::leaveEvent(QEvent *)
{
    if (!isEnabled())
        return;

    state &= ~Hovered; hoverOut = true;
    --hoverLevel;
    if (hoverLevel < 0)
    {
        hoverLevel = 0;
        if (hoverTimer)
            killTimer(hoverTimer);
        hoverTimer = 0;
        return;
    }
    repaint();
    if (!hoverTimer)
        hoverTimer = startTimer ( 50 );
}

void
Button::maximizeChanged(bool maximized)
{
    myType = maximized ? Restore : Max;
    repaint();
}

void
Button::mousePressEvent ( QMouseEvent * event )
{
    if (!isEnabled()) return;

    if (event->button() == Qt::LeftButton)
    {
        state |= Sunken;
        repaint();
    }
}

void
Button::mouseReleaseEvent ( QMouseEvent *event )
{
    state &= ~Sunken;
    const bool under_mouse = Factory::isCompiz() ? underMouse() : rect().contains(event->pos());
    if (!(isEnabled() && under_mouse))
    {
        repaint();
        return;
    }
    KDecorationFactory* f = client->factory(); // needs to be saved before

    const bool lb = (event->button() == Qt::LeftButton);
    const bool rb = (event->button() == Qt::RightButton);
    switch (myType)
    {
    case Close:
        if (lb && client->isCloseable ())
            client->closeWindow();
        break;
    case Min:
        if (lb && client->isMinimizable ())
            client->minimize();
    //       else if (rb) // TODO get dbus interface or whatever to show the Desktop
    //          client->workspace()->setShowingDesktop( true );
        break;
    case Max:
        if (client->isMaximizable ())
        {
            //TODO support alt/ctrl click?!
    //          KDecorationDefines::MaximizeMode mode;
    //          MaximizeRestore    The window is not maximized in any direction.
    //          MaximizeVertical    The window is maximized vertically.
    //          MaximizeHorizontal    The window is maximized horizontally.
    //          MaximizeFull
            client->maximize(event->button());
//             client->setFullscreen(true);
        }
        break;
    case Restore:
        client->maximize(event->button());
        break;
    case Menu:
        //TODO: prepare menu? -> icon, title, stuff
        client->showWindowMenu (mapToGlobal(rect().bottomLeft()));
        break;
    case Help:
        if (lb) client->showContextHelp(); break;
    case Above:
        if (lb) client->setKeepAbove (!client->keepAbove()); break;
    case Below:
        if (lb) client->setKeepBelow (!client->keepBelow()); break;
    case UnAboveBelow:
        if (lb)
        {
            client->setKeepAbove(false);
            client->setKeepBelow(false);
        }
        break;
    case Stick:
    case Unstick:
        if (lb) client->toggleOnAllDesktops();
        else if (rb) client->showDesktopMenu(mapToGlobal(rect().topLeft())); break;
    case Shade:
    case Unshade:
        if (lb) client->setShade(!client->isSetShade()); break;
    case Exposee:
    //       if (rb) //TODO: toggle KWin composite exposé here on lb if available!
            client->showWindowList(mapToGlobal(rect().topLeft())); break;
    case Info:
        client->showInfo(mapToGlobal(rect().topLeft())); break;
    default:
        return; // invalid type
    }
    if( !f->exists( client )) // destroyed, return immediately
        return;
    repaint();
}

static uint fcolors[3] = {0xFFBF0303, 0xFFF3C300, 0xFF00892B};

QColor
Button::color( bool background ) const
{
    KDecorationDefines::ColorType   fgt = KDecorationDefines::ColorButtonBg,
                                    bgt = KDecorationDefines::ColorTitleBlend;
    int bbp = left + client->buttonBoxPos(client->isActive());
    if (bbp < 0 || bbp > 1) // 1 + -1 || 0 + 1 vs. 1 + 1 || 0 + -1
    {
        fgt = KDecorationDefines::ColorFont;
        bgt = KDecorationDefines::ColorTitleBar;
    }
    if ( background )
        return client->color(bgt, client->isActive());
    
    QColor c = client->color(fgt, client->isActive());
    if (fixedColors && myType < Multi)
        c = client->isActive() ? QColor(fcolors[myType]) :
            Colors::mid(c, QColor(fcolors[myType]), 6-hoverLevel, hoverLevel);
    const QColor bg = client->color(bgt, client->isActive());
    if (isEnabled())
        c = Colors::mid(bg, c, 6-hoverLevel, 4);
    else
        c = Colors::mid(bg, c, 6, 1);
    c.setAlpha(c.alpha()*client->buttonOpacity()/100);
//     return c;
    return QColor(59,59,59,255);
}

void
Button::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (!bgPix.isNull())
        p.drawPixmap(0,0, bgPix);

    if ( Factory::buttonGradient() != Gradients::None )
    {
        const QColor bg = color(true);
        const float t = (height()-2)/2.0;
        const float fs = (height()-2)/99.0;
        
        p.end();
        QPixmap mask(size());
        mask.fill(Qt::transparent);
        p.begin(&mask);
        p.setPen(Qt::NoPen);
        p.setBrush( Qt::white );
        p.setRenderHint(QPainter::Antialiasing);
        p.translate( QPoint(t,t) );
        p.scale ( fs, fs );
        p.drawPath(shape[myType]);
        p.end();
        
        p.begin(this);
        const QColor c = color();
        QPixmap texture(size());
        
        texture.fill(Colors::mid(c, Qt::black, 5,4));
        p.drawPixmap(0,0, FX::applyAlpha( texture, mask ) );
        
        texture.fill(Colors::mid(bg, Qt::white ));
        p.drawPixmap(0,2, FX::applyAlpha( texture, mask ) );
        
        QRectF br = shape[myType].boundingRect();
        br.setRect( 0, t + br.y()*fs, texture.width(), br.height() * fs );
        texture.fill(Qt::transparent);
        QPainter p2(&texture);
        p2.drawTiledPixmap(br, Gradients::pix(c, br.height(), Qt::Vertical, (state & Sunken) ? Gradients::Sunken : Factory::buttonGradient()));
        p2.end();
        p.drawPixmap(0,1, FX::applyAlpha( texture, mask ) );
        p.end();

        return;
    }
    // else

    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
//     p.setBrush(color());
    const int slick = Factory::slickButtons();
    
    float fx, fy;
    if (state & Sunken)
        fx = fy = .75;
    else if (slick == 2)
    {
        if (!hoverLevel)
        {
            const float s = width()/5.0;
            p.drawRoundRect(s, 2*s, 3*s, s);
            p.end(); return;
        }
//             6/(b/a-1) = x
        fx = (9+hoverLevel)/15.0;
        fy = (1.5+hoverLevel)/7.5;
        }
    else if (slick)
    {
        if (!hoverLevel)
        {
            const float s = height()/3.0;
            p.drawEllipse(QRectF(s, s, s, s));
            p.end(); return;
        }
        fx = fy = (3+hoverLevel)/9.0;
    }
    else
        fx = fy = (18 + hoverLevel)/24.0;
    const float fs = height()/99.0;
    const float t = height()/2.0;
    p.translate( QPoint(t,t) );
    p.scale ( fs*fx, fs*fy );
//    p.rotate(60*hoverLevel); // too annoying, especially for fast zoom in...
    p.setPen( QPen( Qt::NoPen ) );
    p.setBrush( QColor( 254, 254, 254, 100 ));
    p.drawEllipse( QPoint( width()-5, height() ), 40, 40 );
    p.setBrush( QColor( 59, 59, 59, 255 ));
    p.drawEllipse( QPoint( width()-5, 2 ), 40, 40 );
//     p.setBrush( QBrush( Qt::NoBrush ) );
    p.setBrush( QColor( 255, 255, 255, 255 ) );
    p.drawEllipse( QPoint( 13, 2 ), 15, 15 );
//     p.translate( QPoint(-10,-10) );
//     p.drawPath(shape[myType]);
    p.end();
//     p.setRenderHint( QPainter::Antialiasing, false );

}

void
Button::timerEvent ( QTimerEvent * )
{
    if (hoverOut)
    {
        --hoverLevel;
        if (hoverLevel < 1)
            { killTimer(hoverTimer); hoverTimer = 0; }
    }
    else
    {
        hoverLevel += 2;
        if (hoverLevel > 5)
            { hoverLevel = 6; killTimer(hoverTimer); hoverTimer = 0; }
    }
    repaint();
}

#define CYCLE_ON multiIdx += d;\
if (multiIdx >= mb.size() )\
    multiIdx = 0;\
else if (multiIdx < 0 )\
    multiIdx = mb.size()-1
    
void
Button::wheelEvent(QWheelEvent *e)
{
    if ( iAmScrollable )
    {
        const QVector<Type> &mb = Factory::multiButtons();
        int d = (e->delta() < 0) ? 1 : -1;
        
        CYCLE_ON;
        if (mb.at(multiIdx) == Help && !client->providesContextHelp())
            //       || (mb.at(multiIdx) == Shade && !client->isShadeable()))
        {
            CYCLE_ON;
        }
        
        myType = mb.at(multiIdx);
        if ( (myType == Above && client->keepAbove()) || (myType == Below && client->keepBelow()) )
            myType = UnAboveBelow;
        else if (myType == Stick && client->isOnAllDesktops())
            myType = Unstick;
        else if (myType == Shade && client->isSetShade())
            myType = Unshade;
        
        //TODO: roll max/vert/hori?!
        repaint();
    }
    
    else if ( ( myType == Max || myType == Restore ) && isEnabled() )
        client->tileWindow(e->delta() < 0, e->modifiers() & Qt::ControlModifier, !left);
}
