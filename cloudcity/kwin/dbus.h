//////////////////////////////////////////////////////////////////////////////
//
// -------------------
// Bespin window decoration for KDE.
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

#ifndef XBAR_ADAPTOR_H
#define XBAR_ADAPTOR_H

#include <QDBusAbstractAdaptor>
#include "factory.h"
namespace Bespin
{
class BespinDecoAdaptor : public QDBusAbstractAdaptor
{
   Q_OBJECT
   Q_CLASSINFO("D-Bus Interface", "org.kde.BespinDeco")

private:
    Factory *fac;

public:
    BespinDecoAdaptor(Factory *factory) : QDBusAbstractAdaptor(factory), fac(factory) { }

public slots:
    Q_NOREPLY void styleByPid(qint64 pid, QByteArray data) { fac->learn(pid, data); }
    Q_NOREPLY void forget(qint64 pid) { fac->forget(pid); }
    Q_NOREPLY void setNetbookMode(bool b) { fac->setNetbookMode(b); }
    Q_NOREPLY void updateDeco(uint wid) { fac->updateDeco((WId)wid); }
};
} //namespace
#endif //XBAR_ADAPTOR_H
