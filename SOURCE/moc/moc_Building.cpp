/****************************************************************************
** Meta object code from reading C++ file 'Building.h'
**
** Created: Mon Jan 9 16:25:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Building.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Building.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Building[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Building[] = {
    "Building\0\0hpModify()\0promote()\0"
};

const QMetaObject Building::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Building,
      qt_meta_data_Building, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Building::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Building::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Building::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Building))
        return static_cast<void*>(const_cast< Building*>(this));
    return QObject::qt_metacast(_clname);
}

int Building::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hpModify(); break;
        case 1: promote(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Building::hpModify()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
