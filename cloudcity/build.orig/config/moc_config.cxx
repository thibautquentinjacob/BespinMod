/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created: Thu Mar 1 21:25:20 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../config/config.h"
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
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      16,    7,    7,    7, 0x0a,
      28,   26,    7,    7, 0x0a,
      63,    7,   58,    7, 0x0a,
      70,    7,    7,    7, 0x0a,
      79,    7,    7,    7, 0x0a,
      93,   88,    7,    7, 0x08,
     116,    7,    7,    7, 0x08,
     134,    7,    7,    7, 0x08,
     156,    7,    7,    7, 0x08,
     169,    7,    7,    7, 0x08,
     183,   26,    7,    7, 0x08,
     223,    7,    7,    7, 0x08,
     232,    7,    7,    7, 0x08,
     251,    7,    7,    7, 0x08,
     270,    7,    7,    7, 0x08,
     309,    7,    7,    7, 0x08,
     319,    7,    7,    7, 0x08,
     345,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Config[] = {
    "Config\0\0store()\0restore()\0,\0"
    "restore(QTreeWidgetItem*,int)\0bool\0"
    "save()\0import()\0saveAs()\0text\0"
    "filterPresets(QString)\0handleBgMode(int)\0"
    "handleGrooveMode(int)\0initColors()\0"
    "learnPwChar()\0presetAppsChanged(QTreeWidgetItem*,int)\0"
    "remove()\0reloadColorRoles()\0"
    "setHeader(QString)\0"
    "storedSettigSelected(QTreeWidgetItem*)\0"
    "store2a()\0store2b(QTreeWidgetItem*)\0"
    "showDemo()\0"
};

void Config::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Config *_t = static_cast<Config *>(_o);
        switch (_id) {
        case 0: _t->store(); break;
        case 1: _t->restore(); break;
        case 2: _t->restore((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->import(); break;
        case 5: _t->saveAs(); break;
        case 6: _t->filterPresets((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->handleBgMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->handleGrooveMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->initColors(); break;
        case 10: _t->learnPwChar(); break;
        case 11: _t->presetAppsChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->remove(); break;
        case 13: _t->reloadColorRoles(); break;
        case 14: _t->setHeader((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->storedSettigSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 16: _t->store2a(); break;
        case 17: _t->store2b((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 18: _t->showDemo(); break;
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
