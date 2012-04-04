/****************************************************************************
** Meta object code from reading C++ file 'bespin.h'
**
** Created: Sat Mar 17 15:29:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bespin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bespin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bespin__Style[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
       8,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
      19,   14,

 // slots: signature, parameters, type, tag, flags
      41,   40,   40,   40, 0x08,
      63,   40,   40,   40, 0x08,
     105,  103,   40,   40, 0x08,
     143,   40,   40,   40, 0x08,
     166,   40,   40,   40, 0x08,
     181,   40,   40,   40, 0x08,
     199,   40,   40,   40, 0x08,
     211,   40,   40,   40, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Bespin__Style[] = {
    "Bespin::Style\0true\0X-KDE-CustomElements\0"
    "\0clearScrollbarCache()\0"
    "dockLocationChanged(Qt::DockWidgetArea)\0"
    ",\0focusWidgetChanged(QWidget*,QWidget*)\0"
    "removeAppEventFilter()\0resetRingPix()\0"
    "unlockDocks(bool)\0updateUno()\0"
    "updateBlurRegions()\0"
};

void Bespin::Style::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Style *_t = static_cast<Style *>(_o);
        switch (_id) {
        case 0: _t->clearScrollbarCache(); break;
        case 1: _t->dockLocationChanged((*reinterpret_cast< Qt::DockWidgetArea(*)>(_a[1]))); break;
        case 2: _t->focusWidgetChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 3: _t->removeAppEventFilter(); break;
        case 4: _t->resetRingPix(); break;
        case 5: _t->unlockDocks((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->updateUno(); break;
        case 7: _t->updateBlurRegions(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Bespin::Style::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Bespin::Style::staticMetaObject = {
    { &QCommonStyle::staticMetaObject, qt_meta_stringdata_Bespin__Style,
      qt_meta_data_Bespin__Style, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bespin::Style::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bespin::Style::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bespin::Style::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bespin__Style))
        return static_cast<void*>(const_cast< Style*>(this));
    return QCommonStyle::qt_metacast(_clname);
}

int Bespin::Style::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCommonStyle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
