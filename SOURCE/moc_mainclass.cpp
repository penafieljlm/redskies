/****************************************************************************
** Meta object code from reading C++ file 'mainclass.h'
**
** Created: Mon Nov 28 17:41:02 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainclass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainClass[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      26,   10,   10,   10, 0x08,
      41,   10,   10,   10, 0x08,
      59,   10,   10,   10, 0x08,
      75,   10,   10,   10, 0x08,
      94,   10,   10,   10, 0x08,
     113,   10,   10,   10, 0x08,
     130,   10,   10,   10, 0x08,
     145,   10,   10,   10, 0x08,
     163,   10,   10,   10, 0x08,
     174,   10,   10,   10, 0x08,
     192,   10,   10,   10, 0x08,
     207,   10,   10,   10, 0x08,
     223,   10,   10,   10, 0x08,
     241,   10,   10,   10, 0x08,
     260,   10,   10,   10, 0x08,
     273,   10,   10,   10, 0x08,
     284,   10,   10,   10, 0x08,
     298,   10,   10,   10, 0x08,
     316,   10,   10,   10, 0x08,
     335,   10,   10,   10, 0x08,
     348,   10,   10,   10, 0x08,
     361,   10,   10,   10, 0x08,
     376,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainClass[] = {
    "MainClass\0\0goTransition()\0changeScreen()\0"
    "lightDownButton()\0lightUpButton()\0"
    "lightUpNGSButton()\0lightUpCESButton()\0"
    "execButtonDown()\0execButtonUp()\0"
    "bufferAnimBegin()\0toSplash()\0"
    "toSplashCeption()\0lightUpColor()\0"
    "initializeMap()\0pinchMainCharOn()\0"
    "pinchMainCharOff()\0startKozak()\0"
    "endKozak()\0transToggle()\0quitGameSession()\0"
    "goToResultScreen()\0goToLoader()\0"
    "endKaiAnim()\0kaiAnimFrame()\0soundDecide()\0"
};

const QMetaObject MainClass::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainClass,
      qt_meta_data_MainClass, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainClass))
        return static_cast<void*>(const_cast< MainClass*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: goTransition(); break;
        case 1: changeScreen(); break;
        case 2: lightDownButton(); break;
        case 3: lightUpButton(); break;
        case 4: lightUpNGSButton(); break;
        case 5: lightUpCESButton(); break;
        case 6: execButtonDown(); break;
        case 7: execButtonUp(); break;
        case 8: bufferAnimBegin(); break;
        case 9: toSplash(); break;
        case 10: toSplashCeption(); break;
        case 11: lightUpColor(); break;
        case 12: initializeMap(); break;
        case 13: pinchMainCharOn(); break;
        case 14: pinchMainCharOff(); break;
        case 15: startKozak(); break;
        case 16: endKozak(); break;
        case 17: transToggle(); break;
        case 18: quitGameSession(); break;
        case 19: goToResultScreen(); break;
        case 20: goToLoader(); break;
        case 21: endKaiAnim(); break;
        case 22: kaiAnimFrame(); break;
        case 23: soundDecide(); break;
        default: ;
        }
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
