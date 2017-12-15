/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../3505_Final_Project/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "moveRequested"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "std::string"
QT_MOC_LITERAL(4, 38, 8), // "movement"
QT_MOC_LITERAL(5, 47, 15), // "answerSubmitted"
QT_MOC_LITERAL(6, 63, 6), // "answer"
QT_MOC_LITERAL(7, 70, 14), // "changeMapImage"
QT_MOC_LITERAL(8, 85, 7), // "QImage*"
QT_MOC_LITERAL(9, 93, 8), // "newImage"
QT_MOC_LITERAL(10, 102, 17), // "changePlayerImage"
QT_MOC_LITERAL(11, 120, 5), // "image"
QT_MOC_LITERAL(12, 126, 1), // "x"
QT_MOC_LITERAL(13, 128, 1), // "y"
QT_MOC_LITERAL(14, 130, 17), // "changeGoblinImage"
QT_MOC_LITERAL(15, 148, 1), // "i"
QT_MOC_LITERAL(16, 150, 10), // "killGoblin"
QT_MOC_LITERAL(17, 161, 13), // "showParchment"
QT_MOC_LITERAL(18, 175, 13), // "textToDisplay"
QT_MOC_LITERAL(19, 189, 10), // "takeAnswer"
QT_MOC_LITERAL(20, 200, 14), // "parchmentImage"
QT_MOC_LITERAL(21, 215, 9), // "startGame"
QT_MOC_LITERAL(22, 225, 10), // "difficulty"
QT_MOC_LITERAL(23, 236, 29) // "on_SubmitAnswerButton_clicked"

    },
    "MainWindow\0moveRequested\0\0std::string\0"
    "movement\0answerSubmitted\0answer\0"
    "changeMapImage\0QImage*\0newImage\0"
    "changePlayerImage\0image\0x\0y\0"
    "changeGoblinImage\0i\0killGoblin\0"
    "showParchment\0textToDisplay\0takeAnswer\0"
    "parchmentImage\0startGame\0difficulty\0"
    "on_SubmitAnswerButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   65,    2, 0x0a /* Public */,
      10,    3,   68,    2, 0x0a /* Public */,
      14,    4,   75,    2, 0x0a /* Public */,
      16,    1,   84,    2, 0x0a /* Public */,
      17,    3,   87,    2, 0x0a /* Public */,
      21,    1,   94,    2, 0x0a /* Public */,
      23,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::Int,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   13,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, 0x80000000 | 8,   18,   19,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->moveRequested((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->answerSubmitted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeMapImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 3: _t->changePlayerImage((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->changeGoblinImage((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->killGoblin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->showParchment((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QImage*(*)>(_a[3]))); break;
        case 7: _t->startGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_SubmitAnswerButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::moveRequested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::answerSubmitted)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::moveRequested(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::answerSubmitted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
