/****************************************************************************
** Meta object code from reading C++ file 'menubar.h'
**
** Created: Sun Feb 19 17:51:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XBar/menubar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menubar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      22,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,    8,    8,    8, 0x08,
      53,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MenuBar[] = {
    "MenuBar\0\0hovered(int)\0triggered(int)\0"
    "actionChanged()\0popupClosed()\0"
};

const QMetaObject MenuBar::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_MenuBar,
      qt_meta_data_MenuBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MenuBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MenuBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MenuBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuBar))
        return static_cast<void*>(const_cast< MenuBar*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int MenuBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hovered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: triggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: actionChanged(); break;
        case 3: popupClosed(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MenuBar::hovered(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MenuBar::triggered(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
