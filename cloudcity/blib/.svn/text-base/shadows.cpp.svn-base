/* Bespin widget style for Qt4
   Copyright (C) 2011 Thomas Luebking <thomas.luebking@web.de>

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

#include <QEvent>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QX11Info>

#include <QtDebug>

#include "FX.h"
#include "shadows.h"
#include "tileset.h"
#include "xproperty.h"

using namespace Bespin;

#ifdef Q_WS_X11
class ShadowManager : public QObject {
public:
    ShadowManager() : QObject() {}
protected:
    bool eventFilter(QObject *o, QEvent *e)
    {
        if (e->type() == QEvent::Show)
        if (QWidget *w = qobject_cast<QWidget*>(o))
        if (w->isWindow() && w->testAttribute(Qt::WA_WState_Created) && w->internalWinId())
            Shadows::set(w->winId(), Shadows::Small);
        return false;
    }
};

static ShadowManager *shadowManager = 0;
static uint size[2] = { 12, 64 };
static QColor color(0,0,0,0);
static bool halo(false);

static QPixmap (*pixmaps[2])[8] = {0,0};
static unsigned long globalShadowData[2][12];
#endif

static QPixmap nativePixmap(const QPixmap &qtPix)
{
#ifdef Q_WS_X11
    QPainter pd(const_cast<QPixmap*>(&qtPix)); pd.drawTiledPixmap(qtPix.rect(), FX::dither()); pd.end();
    if (FX::usesXRender() || qtPix.isNull())
        return qtPix;

    Pixmap xPix = XCreatePixmap(QX11Info::display(), QX11Info::appRootWindow(), qtPix.width(), qtPix.height(), 32);
    QPixmap qtXPix(QPixmap::fromX11Pixmap( xPix, QPixmap::ExplicitlyShared ));
    QPainter p(&qtXPix);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, qtPix);
    p.end();
    return qtXPix;
#else
    return qtPix; // just for GCC - makes no sense at all anyway
#endif
}

static unsigned long*
shadowData(Shadows::Type t, bool storeToRoot)
{
#ifdef Q_WS_X11
    unsigned long _12 = 12;
    unsigned long *data = XProperty::get<unsigned long>(QX11Info::appRootWindow(), XProperty::bespinShadow[t-1], XProperty::LONG, &_12);
    if (!data)
    {
#if VARYING_SHADOWS
#warning *** COMPILING WITH VARYING SHADOW PIXMAPS ***
        const int sz = size[t == Shadows::Large];
#else
        int sz = size[1];
#endif
        if (halo)
        {
            globalShadowData[t-1][8] = globalShadowData[t-1][9] = // yes, next line
            globalShadowData[t-1][10] = globalShadowData[t-1][11] = 3*(sz-4)/4;
        }
        else
        {
            globalShadowData[t-1][8] = (sz-4)/2;
            globalShadowData[t-1][9] = 2*(sz-4)/3;
            globalShadowData[t-1][10] = sz-4;
            globalShadowData[t-1][11] = 2*(sz-4)/3;
        }

        if (!pixmaps[t-1])
        {
            QPixmap *store = new QPixmap[8];
            pixmaps[t-1] = (QPixmap (*)[8])store;

            // radial gradient requires the raster engine anyway and we need *working* ... -> QImage
            QImage shadow(2*sz+1, 2*sz+1, QImage::Format_ARGB32);
            shadow.fill(Qt::transparent);
#if VARYING_SHADOWS
            QRadialGradient rg(QPoint(sz+1,sz+1),sz);
            const QRect shadowRect(shadow.rect());
#else
            QRect shadowRect(shadow.rect());
            QRadialGradient rg;
            if (t == Shadows::Small)
            {
                const int d = (size[1] - (size[0]+2))/2;
                shadowRect.adjust(d+3, d, -(d+3), -(d+6));
                sz = qMin(shadowRect.width(), shadowRect.height()) / 2;
                rg = QRadialGradient(shadowRect.center(), sz);
                sz = size[0];
            }
            else
                rg = QRadialGradient(shadowRect.center(), sz);
#endif
            QPainter p(&shadow);
            p.setPen(Qt::NoPen);

            if (halo)
            {
                rg.setColorAt(0, QColor(255,255,255,192)); rg.setColorAt(0.98, QColor(255,255,255,0));
                p.setBrush(rg);
                p.drawRect(shadowRect);
            }

            QColor transparent = color; transparent.setAlpha(0);
            color.setAlpha(112-sz);
            rg.setColorAt(0, color); rg.setColorAt(0.98, transparent);
            p.setBrush(rg);
            p.drawRect(shadowRect);

            rg.setStops(QGradientStops());

            color.setAlpha(96-sz);
            rg.setColorAt(0, color); rg.setColorAt(0.80, transparent);
            p.setBrush(rg);
            p.drawRect(shadowRect);

            rg.setStops(QGradientStops());

            color.setAlpha(72-sz);
            rg.setColorAt(0, color); rg.setColorAt(0.66, transparent);
            p.setBrush(rg);
            p.drawRect(shadowRect);

            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.setRenderHint(QPainter::Antialiasing);
            p.setBrush(Qt::transparent);
            p.drawRoundedRect(shadow.rect().adjusted(globalShadowData[t-1][9], globalShadowData[t-1][8],
                                                     -globalShadowData[t-1][11], -globalShadowData[t-1][10]), 8,8);

            p.end();
#if VARYING_SHADOWS
            Tile::Set shadowSet(shadow,sz,sz,1,1);
#else
            Tile::Set shadowSet(shadow,size[1],size[1],1,1);
#endif

            store[0] = nativePixmap(shadowSet.tile(Tile::TopMid));
            store[1] = nativePixmap(shadowSet.tile(Tile::TopRight));
            store[2] = nativePixmap(shadowSet.tile(Tile::MidRight));
            store[3] = nativePixmap(shadowSet.tile(Tile::BtmRight));
            store[4] = nativePixmap(shadowSet.tile(Tile::BtmMid));
            store[5] = nativePixmap(shadowSet.tile(Tile::BtmLeft));
            store[6] = nativePixmap(shadowSet.tile(Tile::MidLeft));
            store[7] = nativePixmap(shadowSet.tile(Tile::TopLeft));
        }
        for (int i = 0; i < 8; ++i)
            globalShadowData[t-1][i] = (*pixmaps[t-1])[i].handle();

        data = &globalShadowData[t-1][0];
        if (storeToRoot)
            XProperty::set(QX11Info::appRootWindow(), XProperty::bespinShadow[t-1], data, XProperty::LONG, 12);
    }
    return data;
#else
    return 0;  // just for GCC - makes no sense at all anyway
#endif
}

void
Shadows::cleanUp()
{
#ifdef Q_WS_X11
    delete shadowManager; shadowManager = 0;
    for (int i = 0; i < 2; ++i)
    {
        if (pixmaps[i])
        {
            if (!FX::usesXRender())
            {
                for (int j = 0; j < 8; ++j)
                    XFreePixmap(QX11Info::display(), (*pixmaps[i])[j].handle());
            }
            delete [] pixmaps[i];
            pixmaps[i] = 0L;
        }
    }
#endif
}

void
Shadows::manage(QWidget *w)
{
#ifdef Q_WS_X11
    if (!shadowManager)
        shadowManager = new ShadowManager;
    w->removeEventFilter(shadowManager);
    w->installEventFilter(shadowManager);
#endif
}

void
Shadows::set(WId id, Shadows::Type t, bool storeToRoot)
{
#ifdef Q_WS_X11
    if (id == QX11Info::appRootWindow()) {
        qWarning("BESPIN WARNING! Setting shadow to ROOT window is NOT supported");
        return;
    }
    switch(t)
    {
    case Shadows::None:
        XProperty::remove(id, XProperty::kwinShadow);
        break;
    case Shadows::Large:
    case Shadows::Small:
        XProperty::set(id, XProperty::kwinShadow, shadowData(t, storeToRoot), XProperty::LONG, 12);
    default:
        break;
    }
#endif
}

void Shadows::setColor(QColor c)
{
    color = c;
}

void Shadows::setHalo(bool h)
{
    halo = h;
}

void
Shadows::setSize(int small, int big)
{
    size[0] = qMin(72, qMax(8, small));
    size[1] = qMin(72, qMax(8, big));
}