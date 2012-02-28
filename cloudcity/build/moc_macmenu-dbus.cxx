/****************************************************************************
** Meta object code from reading C++ file 'macmenu-dbus.h'
**
** Created: Tue Feb 21 17:58:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../macmenu-dbus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macmenu-dbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bespin__MacMenuAdaptor[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
       6,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
      42,   23,

 // slots: signature, parameters, type, tag, flags
      69,   68,   68,   58, 0x0a,
      80,   68,   68,   58, 0x0a,
     105,   93,   68,   58, 0x0a,
     134,   93,   68,   58, 0x0a,
     167,  163,   68,   58, 0x0a,
     186,  163,   68,   58, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Bespin__MacMenuAdaptor[] = {
    "Bespin::MacMenuAdaptor\0org.kde.XBarClient\0"
    "D-Bus Interface\0Q_NOREPLY\0\0activate()\0"
    "deactivate()\0key,idx,x,y\0"
    "popup(qlonglong,int,int,int)\0"
    "hover(qlonglong,int,int,int)\0key\0"
    "popDown(qlonglong)\0raise(qlonglong)\0"
};

const QMetaObject Bespin::MacMenuAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_Bespin__MacMenuAdaptor,
      qt_meta_data_Bespin__MacMenuAdaptor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bespin::MacMenuAdaptor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bespin::MacMenuAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bespin::MacMenuAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bespin__MacMenuAdaptor))
        return static_cast<void*>(const_cast< MacMenuAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int Bespin::MacMenuAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activate(); break;
        case 1: deactivate(); break;
        case 2: popup((*reinterpret_cast< qlonglong(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: hover((*reinterpret_cast< qlonglong(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: popDown((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        case 5: raise((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
