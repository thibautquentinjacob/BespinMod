//////////////////////////////////////////////////////////////////////////////
// button.h
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

#ifndef BUTTON_H
#define BUTTON_H

#include "../blib/gradients.h"

#include <QWidget>

namespace Bespin
{

class Client;

class Button : public QWidget
{
    Q_OBJECT
public:
    enum State { Normal, Hovered, Sunken };
    enum Type
    {
        Close = 0, Min, Max, Multi,
        Menu, Help, Above, Below, Stick, Shade, Exposee, Info, Special,
        // VertMax, HoriMax,
        Restore, Unstick, UnAboveBelow, Unshade, NumTypes
    };
    Button(Client *parent, Type type, bool left = false);
    static void init(bool leftMenu = false, bool fixedColors = false, int variant = 1);
    bool isEnabled() const;
    void setBg(const QPixmap &pix) { bgPix = pix; }
    inline bool type() {return myType;}
protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void wheelEvent(QWheelEvent*);
private:
    Q_DISABLE_COPY(Button)
    QColor color( bool background = false ) const;
    bool hoverOut, left, iAmScrollable;
    Client *client;
    Type myType;
    int state, multiIdx, hoverTimer, hoverLevel;
    QPixmap bgPix;
    static QPainterPath shape[NumTypes];
    static QString tip[NumTypes];
    static bool fixedColors;
private slots:
    void clientStateChanged(bool);
    void maximizeChanged(bool);
};

} //namespace
#endif
