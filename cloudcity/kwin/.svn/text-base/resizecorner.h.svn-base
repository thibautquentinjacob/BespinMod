//////////////////////////////////////////////////////////////////////////////
//
// -------------------
// Bespin window decoration for KDE
// -------------------
// Copyright (c) 2008/2009 Thomas Lübking <baghira-style@gmx.net>
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

#ifndef RESIZECORNER_H
#define RESIZECORNER_H

#include <QWidget>

namespace Bespin {

class Client;

class ResizeCorner : public QWidget
{
   Q_OBJECT
public:
    ResizeCorner(Client *parent);
    void move ( int x, int y );
    void setColor(const QColor &c);
public slots:
    void raise();
protected:
    bool eventFilter(QObject *obj, QEvent *e);
    void mouseMoveEvent ( QMouseEvent * );
    void mousePressEvent ( QMouseEvent * );
    void mouseReleaseEvent ( QMouseEvent * );
    void paintEvent ( QPaintEvent * );
private:
    bool imCompiz;
    Client *client;
};

} // namespace

#endif //RESIZECORNER_H
