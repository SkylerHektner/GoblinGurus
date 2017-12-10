#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T20:12:34
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3505_Final_Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += "$$PWD/../../Box2D-master/Box2D"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamecontroller.cpp \
    goblin.cpp \
    questionmanager.cpp \
    question.cpp \
    pathfinder.cpp \
    difficultyselector.cpp
    pathfinder.cpp

HEADERS += \
        mainwindow.h \
    gamecontroller.h \
    goblin.h \
    questionmanager.h \
    question.h \
    pathfinder.h \
    difficultyselector.h
    pathfinder.h

FORMS += \
        mainwindow.ui \
    difficultyselector.ui

win32: LIBS += -L"$$PWD/../../SFML-2.4.2/lib" -lsfml-main-d -lsfml-audio-d -lsfml-window-d -lsfml-graphics-d -lsfml-system-d -lsfml-network-d

INCLUDEPATH += "$$PWD/../../SFML-2.4.2/include"
DEPENDPATH += "$$PWD/../../SFML-2.4.2/include"
