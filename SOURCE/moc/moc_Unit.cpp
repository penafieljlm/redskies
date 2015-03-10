/****************************************************************************
** Meta object code from reading C++ file 'Unit.h'
**
** Created: Mon Jan 9 16:25:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Unit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Unit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Unit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      20,   13,    5,    5, 0x0a,
      34,    5,    5,    5, 0x0a,
      42,    5,    5,    5, 0x0a,
      53,    5,    5,    5, 0x0a,
      68,    5,    5,    5, 0x0a,
      76,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Unit[] = {
    "Unit\0\0move()\0target\0attack(Unit*)\0"
    "stand()\0wakeUnit()\0refreshFrame()\0"
    "brain()\0stopSound()\0"
};

const QMetaObject Unit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Unit,
      qt_meta_data_Unit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Unit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Unit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Unit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Unit))
        return static_cast<void*>(const_cast< Unit*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Unit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: move(); break;
        case 1: attack((*reinterpret_cast< Unit*(*)>(_a[1]))); break;
        case 2: stand(); break;
        case 3: wakeUnit(); break;
        case 4: refreshFrame(); break;
        case 5: brain(); break;
        case 6: stopSound(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
