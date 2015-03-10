/****************************************************************************
** Meta object code from reading C++ file 'KozakElement.h'
**
** Created: Thu Nov 24 18:45:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KozakElement.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KozakElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KozakElement[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      20,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   13,   13,   13, 0x0a,
      42,   13,   13,   13, 0x0a,
      51,   13,   13,   13, 0x0a,
      63,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KozakElement[] = {
    "KozakElement\0\0end()\0start()\0startScroll()\0"
    "scroll()\0endScroll()\0animate()\0"
};

const QMetaObject KozakElement::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_KozakElement,
      qt_meta_data_KozakElement, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KozakElement::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KozakElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KozakElement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KozakElement))
        return static_cast<void*>(const_cast< KozakElement*>(this));
    return QLabel::qt_metacast(_clname);
}

int KozakElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: end(); break;
        case 1: start(); break;
        case 2: startScroll(); break;
        case 3: scroll(); break;
        case 4: endScroll(); break;
        case 5: animate(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void KozakElement::end()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void KozakElement::start()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
