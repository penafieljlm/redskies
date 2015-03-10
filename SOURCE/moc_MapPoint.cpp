/****************************************************************************
** Meta object code from reading C++ file 'MapPoint.h'
**
** Created: Mon Nov 28 17:41:07 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MapPoint.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapPoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapPoint[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      23,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      58,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapPoint[] = {
    "MapPoint\0\0deselected()\0selected()\0"
    "animate()\0stopAnimate()\0animateFrame()\0"
};

const QMetaObject MapPoint::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_MapPoint,
      qt_meta_data_MapPoint, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapPoint::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapPoint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapPoint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapPoint))
        return static_cast<void*>(const_cast< MapPoint*>(this));
    return QPushButton::qt_metacast(_clname);
}

int MapPoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deselected(); break;
        case 1: selected(); break;
        case 2: animate(); break;
        case 3: stopAnimate(); break;
        case 4: animateFrame(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MapPoint::deselected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MapPoint::selected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
