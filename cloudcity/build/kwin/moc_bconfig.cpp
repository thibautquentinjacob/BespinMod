/****************************************************************************
** Meta object code from reading C++ file 'bconfig.h'
**
** Created: Sat Mar 17 15:31:23 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../config/bconfig.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BConfig[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      23,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,    8,   33,    8, 0x0a,
      45,    8,    8,    8, 0x0a,
      56,    8,    8,    8, 0x0a,
      64,    8,    8,    8, 0x0a,
      73,    8,    8,    8, 0x0a,
      82,    8,    8,    8, 0x09,
      95,    8,    8,    8, 0x09,
     113,  107,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BConfig[] = {
    "BConfig\0\0changed(bool)\0changed()\0bool\0"
    "save()\0defaults()\0reset()\0import()\0"
    "saveAs()\0checkDirty()\0resetInfo()\0"
    "index\0setComboListInfo(int)\0"
};

void BConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BConfig *_t = static_cast<BConfig *>(_o);
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changed(); break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->defaults(); break;
        case 4: _t->reset(); break;
        case 5: _t->import(); break;
        case 6: _t->saveAs(); break;
        case 7: _t->checkDirty(); break;
        case 8: _t->resetInfo(); break;
        case 9: _t->setComboListInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BConfig::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BConfig,
      qt_meta_data_BConfig, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BConfig::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BConfig))
        return static_cast<void*>(const_cast< BConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int BConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void BConfig::changed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BConfig::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_BConfigDialog[] = {

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
      15,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BConfigDialog[] = {
    "BConfigDialog\0\0accept()\0"
};

void BConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BConfigDialog *_t = static_cast<BConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BConfigDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BConfigDialog,
      qt_meta_data_BConfigDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BConfigDialog))
        return static_cast<void*>(const_cast< BConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
