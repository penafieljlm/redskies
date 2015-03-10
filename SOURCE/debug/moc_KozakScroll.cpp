/****************************************************************************
** Meta object code from reading C++ file 'KozakScroll.h'
**
** Created: Thu Nov 24 18:45:11 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KozakScroll.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KozakScroll.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KozakScroll[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      27,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_KozakScroll[] = {
    "KozakScroll\0\0createKozak()\0cleanKozak()\0"
};

const QMetaObject KozakScroll::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KozakScroll,
      qt_meta_data_KozakScroll, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KozakScroll::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KozakScroll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KozakScroll::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KozakScroll))
        return static_cast<void*>(const_cast< KozakScroll*>(this));
    return QObject::qt_metacast(_clname);
}

int KozakScroll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createKozak(); break;
        case 1: cleanKozak(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
