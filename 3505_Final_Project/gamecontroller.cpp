#include "gamecontroller.h"
#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include <iostream>

// destructor for the Game Controller Class
GameController::~GameController()
{

}

// constructor for the Game Controller Class
GameController::GameController(QObject * parent) : QObject(parent)
{

}

void GameController::loadMapImage()
{
    QImage testImage("testMap.jpg");

    emit changeMapImageRequest(&testImage);
}
