/****************************************************************************
** Meta object code from reading C++ file 'basic.h'
**
** Created: Tue Feb 21 17:58:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../animator/basic.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Animator__Basic[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Animator__Basic[] = {
    "Animator::Basic\0\0release_s(QObject*)\0"
};

const QMetaObject Animator::Basic::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Animator__Basic,
      qt_meta_data_Animator__Basic, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Animator::Basic::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Animator::Basic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Animator::Basic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Animator__Basic))
        return static_cast<void*>(const_cast< Basic*>(this));
    return QObject::qt_metacast(_clname);
}

int Animator::Basic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: release_s((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
