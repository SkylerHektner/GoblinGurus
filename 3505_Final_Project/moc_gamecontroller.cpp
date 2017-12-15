/****************************************************************************
** Meta object code from reading C++ file 'gamecontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamecontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameController_t {
    QByteArrayData data[23];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameController_t qt_meta_stringdata_GameController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GameController"
QT_MOC_LITERAL(1, 15, 21), // "changeMapImageRequest"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 7), // "QImage*"
QT_MOC_LITERAL(4, 46, 5), // "image"
QT_MOC_LITERAL(5, 52, 24), // "changePlayerImageRequest"
QT_MOC_LITERAL(6, 77, 1), // "x"
QT_MOC_LITERAL(7, 79, 1), // "y"
QT_MOC_LITERAL(8, 81, 13), // "showParchment"
QT_MOC_LITERAL(9, 95, 12), // "QuestionText"
QT_MOC_LITERAL(10, 108, 10), // "takeAnswer"
QT_MOC_LITERAL(11, 119, 12), // "updateHealth"
QT_MOC_LITERAL(12, 132, 6), // "health"
QT_MOC_LITERAL(13, 139, 10), // "michaelBay"
QT_MOC_LITERAL(14, 150, 24), // "changeGoblinImageRequest"
QT_MOC_LITERAL(15, 175, 1), // "i"
QT_MOC_LITERAL(16, 177, 10), // "killGoblin"
QT_MOC_LITERAL(17, 188, 13), // "moveRequested"
QT_MOC_LITERAL(18, 202, 11), // "std::string"
QT_MOC_LITERAL(19, 214, 8), // "movement"
QT_MOC_LITERAL(20, 223, 14), // "answerReceived"
QT_MOC_LITERAL(21, 238, 6), // "answer"
QT_MOC_LITERAL(22, 245, 12) // "tickGoblinAI"

    },
    "GameController\0changeMapImageRequest\0"
    "\0QImage*\0image\0changePlayerImageRequest\0"
    "x\0y\0showParchment\0QuestionText\0"
    "takeAnswer\0updateHealth\0health\0"
    "michaelBay\0changeGoblinImageRequest\0"
    "i\0killGoblin\0moveRequested\0std::string\0"
    "movement\0answerReceived\0answer\0"
    "tickGoblinAI"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    3,   67,    2, 0x06 /* Public */,
       8,    3,   74,    2, 0x06 /* Public */,
      11,    1,   81,    2, 0x06 /* Public */,
      13,    2,   84,    2, 0x06 /* Public */,
      14,    4,   89,    2, 0x06 /* Public */,
      16,    1,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  101,    2, 0x0a /* Public */,
      20,    1,  104,    2, 0x0a /* Public */,
      22,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, 0x80000000 | 3,    9,   10,    4,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    6,    7,   15,
    QMetaType::Void, QMetaType::Int,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,

       0        // eod
};

void GameController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameController *_t = static_cast<GameController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeMapImageRequest((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 1: _t->changePlayerImageRequest((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->showParchment((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QImage*(*)>(_a[3]))); break;
        case 3: _t->updateHealth((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->michaelBay((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->changeGoblinImageRequest((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->killGoblin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->moveRequested((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->answerReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->tickGoblinAI(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameController::*_t)(QImage * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::changeMapImageRequest)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(QImage * , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::changePlayerImageRequest)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(QString , bool , QImage * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::showParchment)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::updateHealth)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::michaelBay)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(QImage * , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::changeGoblinImageRequest)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (GameController::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameController::killGoblin)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject GameController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GameController.data,
      qt_meta_data_GameController,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GameController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameController.stringdata0))
        return static_cast<void*>(const_cast< GameController*>(this));
    return QObject::qt_metacast(_clname);
}

int GameController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GameController::changeMapImageRequest(QImage * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameController::changePlayerImageRequest(QImage * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameController::showParchment(QString _t1, bool _t2, QImage * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameController::updateHealth(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameController::michaelBay(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GameController::changeGoblinImageRequest(QImage * _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GameController::killGoblin(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
