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

#include <QApplication>
#include <QDBusConnection>
#include "xbar.h"
#include "dbus.h"

using namespace Bespin;

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   XBar *bar = new XBar;
   XBarAdaptor *adapt = new XBarAdaptor(bar);
   QDBusConnection::sessionBus().registerService("org.kde.XBar");
   QDBusConnection::sessionBus().registerObject("/XBar", bar);
   bar->show();
   return app.exec();
}
