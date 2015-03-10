/****************************************************************************
** Meta object code from reading C++ file 'ChallengeEngine.h'
**
** Created: Mon Nov 28 17:41:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ChallengeEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChallengeEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChallengeEngine[] = {

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
      17,   16,   16,   16, 0x0a,
      39,   16,   16,   16, 0x0a,
      62,   16,   16,   16, 0x08,
      79,   16,   16,   16, 0x08,
      92,   16,   16,   16, 0x08,
     103,   16,   16,   16, 0x08,
     118,   16,   16,   16, 0x08,
     141,   16,   16,   16, 0x08,
     160,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ChallengeEngine[] = {
    "ChallengeEngine\0\0goToChallengeScreen()\0"
    "leaveChallengeScreen()\0startChallenge()\0"
    "startRound()\0endRound()\0endChallenge()\0"
    "goToEndChallengePage()\0leaveChooseColor()\0"
    "setAIInterval()\0"
};

const QMetaObject ChallengeEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChallengeEngine,
      qt_meta_data_ChallengeEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChallengeEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChallengeEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChallengeEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChallengeEngine))
        return static_cast<void*>(const_cast< ChallengeEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int ChallengeEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: goToChallengeScreen(); break;
        case 1: leaveChallengeScreen(); break;
        case 2: startChallenge(); break;
        case 3: startRound(); break;
        case 4: endRound(); break;
        case 5: endChallenge(); break;
        case 6: goToEndChallengePage(); break;
        case 7: leaveChooseColor(); break;
        case 8: setAIInterval(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
