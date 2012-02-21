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

#ifndef XBAR_ADAPTOR_H
#define XBAR_ADAPTOR_H

#include <QDBusAbstractAdaptor>
#include "xbar.h"

class XBarAdaptor : public QDBusAbstractAdaptor
{
   Q_OBJECT
   Q_CLASSINFO("D-Bus Interface", "org.kde.XBar")

private:
   XBar *bar;

public:
   XBarAdaptor(XBar *xBar) : QDBusAbstractAdaptor(xBar), bar(xBar) { }

public slots:
   Q_NOREPLY void registerMenu(const QString &service, qlonglong key, const QString &title, const QStringList &entries)
   { bar->registerMenu(service, key, title, entries); }
   Q_NOREPLY void unregisterMenu(qlonglong key) { bar->unregisterMenu(key); }

   Q_NOREPLY void setOpenPopup(int idx) { bar->setOpenPopup(idx); }
   Q_NOREPLY void requestFocus(qlonglong key) { bar->requestFocus(key); }
   Q_NOREPLY void releaseFocus(qlonglong key) { bar->releaseFocus(key); }
   Q_NOREPLY void reparent(qlonglong oldKey, qlonglong newKey)
   { bar->reparent(oldKey, newKey); }
   Q_NOREPLY void addEntry(qlonglong key, int idx, const QString &entry)
   { bar->changeEntry(key, idx, entry, true); }
   Q_NOREPLY void changeEntry(qlonglong key, int idx, const QString &entry)
   { bar->changeEntry(key, idx, entry, false); }
   Q_NOREPLY void removeEntry(qlonglong key, int idx) { bar->changeEntry(key, idx); }

};

#endif //XBAR_ADAPTOR_H
