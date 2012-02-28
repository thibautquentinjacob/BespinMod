/****************************************************************************
** Meta object code from reading C++ file 'visualframe.h'
**
** Created: Tue Feb 21 17:58:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../visualframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VisualFramePart[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_VisualFramePart[] = {
    "VisualFramePart\0"
};

const QMetaObject VisualFramePart::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VisualFramePart,
      qt_meta_data_VisualFramePart, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VisualFramePart::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VisualFramePart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VisualFramePart::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VisualFramePart))
        return static_cast<void*>(const_cast< VisualFramePart*>(this));
    return QWidget::qt_metacast(_clname);
}

int VisualFramePart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VisualFrame[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      20,   12,   12,   12, 0x0a,
      27,   12,   12,   12, 0x0a,
      35,   12,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      54,   12,   12,   12, 0x08,
      72,   12,   12,   12, 0x08,
      90,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VisualFrame[] = {
    "VisualFrame\0\0show()\0hide()\0raise()\0"
    "update()\0repaint()\0correctPosition()\0"
    "deleteMuchLater()\0hideMe()\0"
};

const QMetaObject VisualFrame::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisualFrame,
      qt_meta_data_VisualFrame, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VisualFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VisualFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VisualFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VisualFrame))
        return static_cast<void*>(const_cast< VisualFrame*>(this));
    return QObject::qt_metacast(_clname);
}

int VisualFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: show(); break;
        case 1: hide(); break;
        case 2: raise(); break;
        case 3: update(); break;
        case 4: repaint(); break;
        case 5: correctPosition(); break;
        case 6: deleteMuchLater(); break;
        case 7: hideMe(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
