/****************************************************************************
** Meta object code from reading C++ file 'hover.h'
**
** Created: Sun Feb 19 17:49:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../animator/hover.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hover.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Animator__Hover[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   22,   17,   16, 0x09,
      71,   65,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Animator__Hover[] = {
    "Animator::Hover\0\0bool\0object,event\0"
    "eventFilter(QObject*,QEvent*)\0event\0"
    "timerEvent(QTimerEvent*)\0"
};

const QMetaObject Animator::Hover::staticMetaObject = {
    { &Basic::staticMetaObject, qt_meta_stringdata_Animator__Hover,
      qt_meta_data_Animator__Hover, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Animator::Hover::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Animator::Hover::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Animator::Hover::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Animator__Hover))
        return static_cast<void*>(const_cast< Hover*>(this));
    return Basic::qt_metacast(_clname);
}

int Animator::Hover::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Basic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
