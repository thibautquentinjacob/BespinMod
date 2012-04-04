/****************************************************************************
** Meta object code from reading C++ file 'hoverindex.h'
**
** Created: Thu Mar 1 21:24:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../animator/hoverindex.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hoverindex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Animator__HoverIndex[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Animator__HoverIndex[] = {
    "Animator::HoverIndex\0\0o\0release(QObject*)\0"
};

void Animator::HoverIndex::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HoverIndex *_t = static_cast<HoverIndex *>(_o);
        switch (_id) {
        case 0: _t->release((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Animator::HoverIndex::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Animator::HoverIndex::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Animator__HoverIndex,
      qt_meta_data_Animator__HoverIndex, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Animator::HoverIndex::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Animator::HoverIndex::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Animator::HoverIndex::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Animator__HoverIndex))
        return static_cast<void*>(const_cast< HoverIndex*>(this));
    return QObject::qt_metacast(_clname);
}

int Animator::HoverIndex::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
