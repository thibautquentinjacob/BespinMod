/****************************************************************************
** Meta object code from reading C++ file 'visualframe.h'
**
** Created: Sat Mar 17 15:29:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../visualframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VisualFramePart[] = {

 // content:
       6,       // revision
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

void VisualFramePart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VisualFramePart::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VisualFramePart::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VisualFramePart,
      qt_meta_data_VisualFramePart, &staticMetaObjectExtraData }
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
       6,       // revision
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

void VisualFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VisualFrame *_t = static_cast<VisualFrame *>(_o);
        switch (_id) {
        case 0: _t->show(); break;
        case 1: _t->hide(); break;
        case 2: _t->raise(); break;
        case 3: _t->update(); break;
        case 4: _t->repaint(); break;
        case 5: _t->correctPosition(); break;
        case 6: _t->deleteMuchLater(); break;
        case 7: _t->hideMe(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VisualFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VisualFrame::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisualFrame,
      qt_meta_data_VisualFrame, &staticMetaObjectExtraData }
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
