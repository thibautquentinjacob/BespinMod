/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created: Sun Feb 19 17:58:00 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../config/config.h"
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
        case 0: store(); break;
        case 1: restore(); break;
        case 2: restore((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: import(); break;
        case 5: saveAs(); break;
        case 6: filterPresets((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: handleBgMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: handleGrooveMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: initColors(); break;
        case 10: learnPwChar(); break;
        case 11: presetAppsChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: remove(); break;
        case 13: reloadColorRoles(); break;
        case 14: setHeader((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: storedSettigSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 16: store2a(); break;
        case 17: store2b((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 18: showDemo(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
