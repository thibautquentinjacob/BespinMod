/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created: Sun Feb 19 17:51:29 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../kwin/config.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Config[] = {

 // content:
       5,       // revision
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

const QMetaObject Config::staticMetaObject = {
    { &BConfig::staticMetaObject, qt_meta_stringdata_Config,
      qt_meta_data_Config, 0 }
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
        switch (_id) {
        case 0: createNewPreset(); break;
        case 1: deleteCurrentPreset(); break;
        case 2: presetChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 3: save((*reinterpret_cast< KConfigGroup(*)>(_a[1]))); break;
        case 4: catchClones((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: watchBgMode(); break;
        case 6: watchButtonGradient(); break;
        case 7: watchDecoGradient(); break;
        case 8: watchShadowSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
