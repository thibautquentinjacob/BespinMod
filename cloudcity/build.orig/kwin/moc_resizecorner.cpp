/****************************************************************************
** Meta object code from reading C++ file 'resizecorner.h'
**
** Created: Tue Feb 7 20:35:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../kwin/resizecorner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resizecorner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bespin__ResizeCorner[] = {

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
      22,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Bespin__ResizeCorner[] = {
    "Bespin::ResizeCorner\0\0raise()\0"
};

const QMetaObject Bespin::ResizeCorner::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Bespin__ResizeCorner,
      qt_meta_data_Bespin__ResizeCorner, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bespin::ResizeCorner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bespin::ResizeCorner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bespin::ResizeCorner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bespin__ResizeCorner))
        return static_cast<void*>(const_cast< ResizeCorner*>(this));
    return QWidget::qt_metacast(_clname);
}

int Bespin::ResizeCorner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: raise(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
