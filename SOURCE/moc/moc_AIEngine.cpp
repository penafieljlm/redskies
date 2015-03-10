/****************************************************************************
** Meta object code from reading C++ file 'AIEngine.h'
**
** Created: Mon Jan 9 16:25:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AIEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AIEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AIEngine[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      18,    9,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AIEngine[] = {
    "AIEngine\0\0brain()\0startAI()\0stopAI()\0"
};

const QMetaObject AIEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AIEngine,
      qt_meta_data_AIEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AIEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AIEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AIEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AIEngine))
        return static_cast<void*>(const_cast< AIEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int AIEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: brain(); break;
        case 1: startAI(); break;
        case 2: stopAI(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
