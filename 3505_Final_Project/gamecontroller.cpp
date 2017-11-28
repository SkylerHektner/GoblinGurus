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
    // make the player sprite a black square for testing
    playerSprite = new QImage(40, 40, QImage::Format_ARGB32);
    playerSprite->fill(Qt::GlobalColor::black);

    // fill the collision point array with points
    collisionPoints->push_back(std::pair<int, int>(1, 1));
}

// private method to load in a map Image. Will likely take in a QImage later
void GameController::loadMapImage()
{
    QImage testImage("testMap.jpg");

    emit changeMapImageRequest(&testImage);
}

void GameController::loadPlayerImage()
{
    emit changePlayerImageRequest(playerSprite, PlayerPosX * gridRatio, PlayerPosY * gridRatio);
}

// public slot for moving the character
void GameController::moveRequested(std::string movement)
{
    // record old positions incase there ends up being a collision
    int oldPosX, oldPosY;
    oldPosX = PlayerPosX;
    oldPosY = PlayerPosY;

    // calculate the movement
    if (movement == "UP" && PlayerPosY > 0)
    {
        PlayerPosY--;
    }
    else if (movement == "DOWN" && PlayerPosY < maxGridSizeY)
    {
        PlayerPosY++;
    }
    else if (movement == "LEFT" && PlayerPosX > 0)
    {
        PlayerPosX--;
    }
    else if (movement == "RIGHT" && PlayerPosX < maxGridSizeX)
    {
        PlayerPosX++;
    }

    // check for collision and revert movement if necessary
    for (int i = 0; i < collisionPoints->size(); i++)
    {
        if (collisionPoints->at(i) == std::pair<int, int>(PlayerPosX, PlayerPosY))
        {
            PlayerPosX = oldPosX;
            PlayerPosY = oldPosY;
        }
    }

    // tell the view to show where the player now is
    loadPlayerImage();
}
