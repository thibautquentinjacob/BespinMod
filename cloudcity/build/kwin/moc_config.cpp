/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created: Sat Mar 17 15:31:23 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../kwin/config.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Config[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      26,    7,    7,    7, 0x0a,
      50,   48,    7,    7, 0x0a,
      99,    7,    7,    7, 0x0a,
     119,    7,    7,    7, 0x08,
     149,    7,    7,    7, 0x08,
     163,    7,    7,    7, 0x08,
     185,    7,    7,    7, 0x08,
     205,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Config[] = {
    "Config\0\0createNewPreset()\0"
    "deleteCurrentPreset()\0,\0"
    "presetChanged(QListWidgetItem*,QListWidgetItem*)\0"
    "save(KConfigGroup&)\0catchClones(QListWidgetItem*)\0"
    "watchBgMode()\0watchButtonGradient()\0"
    "watchDecoGradient()\0watchShadowSize(int)\0"
};

void Config::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Config *_t = static_cast<Config *>(_o);
        switch (_id) {
        case 0: _t->createNewPreset(); break;
        case 1: _t->deleteCurrentPreset(); break;
        case 2: _t->presetChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->save((*reinterpret_cast< KConfigGroup(*)>(_a[1]))); break;
        case 4: _t->catchClones((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->watchBgMode(); break;
        case 6: _t->watchButtonGradient(); break;
        case 7: _t->watchDecoGradient(); break;
        case 8: _t->watchShadowSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Config::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Config::staticMetaObject = {
    { &BConfig::staticMetaObject, qt_meta_stringdata_Config,
      qt_meta_data_Config, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Config::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Config::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Config::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Config))
        return static_cast<void*>(const_cast< Config*>(this));
    return BConfig::qt_metacast(_clname);
}

int Config::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BConfig::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
