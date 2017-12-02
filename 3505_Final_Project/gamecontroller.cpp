#include "gamecontroller.h"
#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include <iostream>
#include "goblin.h"

// destructor for the Game Controller Class
GameController::~GameController()
{

}

// constructor for the Game Controller Class
GameController::GameController(QObject * parent) : QObject(parent)
{
    // Load the player sprites
    float ratio = 1;
    playerSprite_f = new QImage("../Assets/spr_main_f.png");
    playerSprite_f->setDevicePixelRatio(ratio);
    playerSprite_b = new QImage("../Assets/spr_main_b.png");
    playerSprite_b->setDevicePixelRatio(ratio);
    playerSprite_l = new QImage("../Assets/spr_main_l.png");
    playerSprite_l->setDevicePixelRatio(ratio);
    playerSprite_r = new QImage("../Assets/spr_main_r.png");
    playerSprite_r->setDevicePixelRatio(ratio);

    // fill the collision point array with points
    collisionPoints->push_back(std::pair<int, int>(1, 1));

    // add some goblins to the goblinVector
    goblinVector->push_back(new goblin(4, 4, "What is the meaning of life!?", 42));


}

// private method to load in a map Image. Will likely take in a QImage later
void GameController::loadMapImage()
{
    QImage testImage("../Assets/level_template.jpg");

    emit changeMapImageRequest(&testImage);
}

void GameController::loadPlayerImage()
{
    if (lastMoveDirection == 'f')
    {
        emit changePlayerImageRequest(playerSprite_f, PlayerPosX * gridRatio + gridOffsetX, PlayerPosY * gridRatio + gridOffsetY);
    }
    else if (lastMoveDirection == 'b')
    {
        emit changePlayerImageRequest(playerSprite_b, PlayerPosX * gridRatio + gridOffsetX, PlayerPosY * gridRatio + gridOffsetY);
    }
    else if (lastMoveDirection == 'l')
    {
        emit changePlayerImageRequest(playerSprite_l, PlayerPosX * gridRatio + gridOffsetX, PlayerPosY * gridRatio + gridOffsetY);
    }
    else if (lastMoveDirection == 'r')
    {
        emit changePlayerImageRequest(playerSprite_r, PlayerPosX * gridRatio + gridOffsetX, PlayerPosY * gridRatio + gridOffsetY);
    }
}

void GameController::loadGoblinImages()
{
    for(int i = 0; i < goblinVector->size(); i++)
    {
        emit changeGoblinImageRequest(goblinVector->at(i)->goblinSprite,
                                      goblinVector->at(i)->posX * gridRatio + gridOffsetX,
                                      goblinVector->at(i)->posY * gridRatio + gridOffsetY,
                                      i);
    }
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
        lastMoveDirection = 'b';
    }
    else if (movement == "DOWN" && PlayerPosY < maxGridSizeY)
    {
        PlayerPosY++;
        lastMoveDirection = 'f';
    }
    else if (movement == "LEFT" && PlayerPosX > 0)
    {
        PlayerPosX--;
        lastMoveDirection = 'l';
    }
    else if (movement == "RIGHT" && PlayerPosX < maxGridSizeX)
    {
        PlayerPosX++;
        lastMoveDirection = 'r';
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
