#include "gamecontroller.h"
#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include <iostream>
#include "goblin.h"
#include "questionmanager.h"
#include "question.h"
#include <QString>

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

    // populate the collision point vector with wall positions for level 1
    generateLevelCollisionPoints();

    // load in the parchmentImage
    parchmentImage = new QImage("../Assets/parchment.png");

    // define player starting location (level 1)
    PlayerPosX = 14;
    PlayerPosY = 4;
}

void GameController::startGame()
{
    loadMapImage();
    loadPlayerImage();
    generateGoblins();
    loadGoblinImages();

    QString health(std::to_string(playerHealth).data());
    emit updateHealth(health);
}

// private method to load in a map Image. Will likely take in a QImage later
void GameController::loadMapImage()
{
    QString filepath = "../Assets/level_" + QString::number(level) + ".jpg";
    QImage testImage(filepath);

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
    oldPosX = PlayerPosX;
    oldPosY = PlayerPosY;

    if (moveAllowed)
    {
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

    // check for collision with goblins
    for (int i = 0; i < goblinVector->size();i++)
    {
        if (goblinVector->at(i)->posX == PlayerPosX && goblinVector->at(i)->posY == PlayerPosY)
        {
            moveAllowed = false;
            emit showParchment(goblinVector->at(i)->question, true, parchmentImage);
        }
    }

    // tell the view to show where the player now is
    loadPlayerImage();
}

// the slot used to catch an answer submitted in the view
void GameController::answerReceived(int answer)
{
    // allow the player to move again
    moveAllowed = true;

    // find the goblin currently colliding with the player and kill them if the player answered correctly
    for (int i = 0; i < goblinVector->size();i++)
    {
        if (goblinVector->at(i)->posX == PlayerPosX && goblinVector->at(i)->posY == PlayerPosY)
        {
            // convenient debug line to show us the correct answer to the question
            std::cout << goblinVector->at(i)->answer << std::endl;
            std::cout << goblinVector->size() << std::endl;
            if (goblinVector->at(i)->answer == answer)
            {
                // remove the goblin from the vector, delete it, and shift back all remaining elements in the vector
                delete goblinVector->at(i);
                if(goblinVector->size() == 1)
                {
                    generateNextLevel();
                }
                else
                {
                    // create a new vector to store the goblins. We have to do this to reset vector.size
                    std::vector<goblin*> * newVector = new std::vector<goblin*>();

                    // store all old goblins in the new vector except the one we are killing
                    for(int v = 0; v < goblinVector->size(); v++)
                    {
                        if (v != i)
                        {
                            newVector->push_back(goblinVector->at(v));
                        }
                    }

                    // delete the old goblin vector and assign goblinVector to the new vector
                    delete goblinVector;
                    goblinVector = newVector;

                    // tell the screen to update
                    emit loadGoblinImages();
                    // make sure we are not rendering the slot for the old goblin
                    emit killGoblin(goblinVector->size());
                }
            }

            else
            {
                // player takes damage
                playerHealth -= goblinAttackDamage;
                QString health(std::to_string(playerHealth).data());
                emit updateHealth(health);

                // player returns to pos before attack
                PlayerPosX = oldPosX;
                PlayerPosY = oldPosY;
                emit loadPlayerImage();

                // for now, application simply terminates on loss
                if (playerHealth <= 0)
                {
                    exit(EXIT_SUCCESS);
                }
            }


        }
    }
}

// re-populate the collision vector with the proper points based on the level
void GameController::generateLevelCollisionPoints()
{
    collisionPoints->clear();

    if(level == 1)
    {
        // create border points
        for(int i = 0; i < 16; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 0));
            collisionPoints->push_back(std::pair<int, int>(i, 9));
        }
        for(int i = 0; i < 10; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(0, i));
            collisionPoints->push_back(std::pair<int, int>(15, i));
        }

        // define level 1 inner walls
        collisionPoints->push_back(std::pair<int, int>(1, 4));
        collisionPoints->push_back(std::pair<int, int>(1, 5));
        collisionPoints->push_back(std::pair<int, int>(3, 4));
        collisionPoints->push_back(std::pair<int, int>(3, 5));
        collisionPoints->push_back(std::pair<int, int>(4, 4));
        collisionPoints->push_back(std::pair<int, int>(4, 5));
        collisionPoints->push_back(std::pair<int, int>(6, 4));
        collisionPoints->push_back(std::pair<int, int>(6, 5));
        collisionPoints->push_back(std::pair<int, int>(7, 1));
        collisionPoints->push_back(std::pair<int, int>(7, 3));
        collisionPoints->push_back(std::pair<int, int>(7, 4));
        collisionPoints->push_back(std::pair<int, int>(7, 5));
        collisionPoints->push_back(std::pair<int, int>(7, 6));
        collisionPoints->push_back(std::pair<int, int>(7, 7));
        collisionPoints->push_back(std::pair<int, int>(7, 8));
        collisionPoints->push_back(std::pair<int, int>(10, 3));
        collisionPoints->push_back(std::pair<int, int>(10, 6));
        collisionPoints->push_back(std::pair<int, int>(11, 2));
        collisionPoints->push_back(std::pair<int, int>(11, 3));
        collisionPoints->push_back(std::pair<int, int>(11, 6));
        collisionPoints->push_back(std::pair<int, int>(11, 7));
        collisionPoints->push_back(std::pair<int, int>(12, 3));
        collisionPoints->push_back(std::pair<int, int>(12, 6));
    }

    if(level == 2)
    {
        // create border points
        for(int i = 0; i < 16; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 0));
            collisionPoints->push_back(std::pair<int, int>(i, 9));
        }
        for(int i = 0; i < 10; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(0, i));
            collisionPoints->push_back(std::pair<int, int>(15, i));
        }

        collisionPoints->push_back(std::pair<int, int>(3, 1));
        collisionPoints->push_back(std::pair<int, int>(11, 1));
        collisionPoints->push_back(std::pair<int, int>(5, 2));
        collisionPoints->push_back(std::pair<int, int>(7, 2));
        collisionPoints->push_back(std::pair<int, int>(9, 2));
        collisionPoints->push_back(std::pair<int, int>(3, 3));
        collisionPoints->push_back(std::pair<int, int>(11, 3));
        for (int i = 2; i < 13; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 4));
        }
        collisionPoints->push_back(std::pair<int, int>(14, 4));
        collisionPoints->push_back(std::pair<int, int>(3, 5));
        collisionPoints->push_back(std::pair<int, int>(11, 5));
        collisionPoints->push_back(std::pair<int, int>(6, 6));
        collisionPoints->push_back(std::pair<int, int>(7, 6));
        collisionPoints->push_back(std::pair<int, int>(8, 6));
        collisionPoints->push_back(std::pair<int, int>(6, 7));
        collisionPoints->push_back(std::pair<int, int>(7, 7));
        collisionPoints->push_back(std::pair<int, int>(8, 7));
        collisionPoints->push_back(std::pair<int, int>(3, 8));
        collisionPoints->push_back(std::pair<int, int>(11, 8));
    }

    if(level == 3)
    {
        // create border points
        for(int i = 0; i < 16; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 0));
            collisionPoints->push_back(std::pair<int, int>(i, 9));
        }
        for(int i = 0; i < 10; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(0, i));
            collisionPoints->push_back(std::pair<int, int>(15, i));
        }

        collisionPoints->push_back(std::pair<int, int>(4, 1));
        collisionPoints->push_back(std::pair<int, int>(10, 1));
        for(int i = 2; i < 9; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 2));
        }
        collisionPoints->push_back(std::pair<int, int>(10, 2));
        collisionPoints->push_back(std::pair<int, int>(12, 2));
        collisionPoints->push_back(std::pair<int, int>(14, 2));
        collisionPoints->push_back(std::pair<int, int>(12, 3));
        collisionPoints->push_back(std::pair<int, int>(1, 4));
        collisionPoints->push_back(std::pair<int, int>(2, 4));
        collisionPoints->push_back(std::pair<int, int>(3, 4));
        for(int i = 5; i < 13; i++)
        {
            collisionPoints->push_back(std::pair<int, int>(i, 4));
        }
        collisionPoints->push_back(std::pair<int, int>(14, 4));
        collisionPoints->push_back(std::pair<int, int>(5, 5));
        collisionPoints->push_back(std::pair<int, int>(9, 5));
        collisionPoints->push_back(std::pair<int, int>(2, 6));
        collisionPoints->push_back(std::pair<int, int>(3, 6));
        collisionPoints->push_back(std::pair<int, int>(5, 6));
        collisionPoints->push_back(std::pair<int, int>(7, 6));
        collisionPoints->push_back(std::pair<int, int>(11, 6));
        collisionPoints->push_back(std::pair<int, int>(12, 6));
        collisionPoints->push_back(std::pair<int, int>(13, 6));
        collisionPoints->push_back(std::pair<int, int>(3, 7));
        collisionPoints->push_back(std::pair<int, int>(5, 7));
        collisionPoints->push_back(std::pair<int, int>(7, 7));
        collisionPoints->push_back(std::pair<int, int>(8, 7));
        collisionPoints->push_back(std::pair<int, int>(9, 7));
        collisionPoints->push_back(std::pair<int, int>(11, 7));
        collisionPoints->push_back(std::pair<int, int>(13, 7));
        collisionPoints->push_back(std::pair<int, int>(5, 8));
        collisionPoints->push_back(std::pair<int, int>(11, 8));
    }
}

// this methods spawns goblins based on the level entered
void GameController::generateGoblins()
{
    goblinVector->clear();
    if (level == 1)
    {
        Question q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(2, 2, q.text, q.answer));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(5, 2, q.text, q.answer));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(2, 7, q.text, q.answer));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(5, 7, q.text, q.answer));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(9, 2, q.text, q.answer));
    }
    else if (level == 2)
    {
        Question q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(13, 7, q.text, q.answer));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(7, 8, q.text, q.answer));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(7, 5, q.text, q.answer));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(2, 5, q.text, q.answer));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(4, 3, q.text, q.answer));
        /*q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(8, 2, q.text, q.answer));
        q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(1, 1, q.text, q.answer));
        q = questionManager->GetQuestion(0);*/
    }
    else if(level == 3)
    {
        Question q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(12, 7, q.text, q.answer));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(14, 1, q.text, q.answer));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(6, 5, q.text, q.answer));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(2, 5, q.text, q.answer));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(2, 7, q.text, q.answer));
        /*q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(5, 1, q.text, q.answer));
        q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(3, 1, q.text, q.answer));
        q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(11, 3, q.text, q.answer));
        q = questionManager->GetQuestion(0);*/
    }
    else
    {
        std::cout <<"you have not programmed in goblin spawn locations for this level in GameController::generateGoblins" << std::endl;
    }
}

void GameController::generateNextLevel()
{
    // loops around after completion
    if (level >= 3)
    {
        level = 1;
    }
    else
    {
        level++;
    }
    loadMapImage();
    generateLevelCollisionPoints();
    generateGoblins();
    playerHealth = 100;

    // sets the players starting location for the level
    switch (level)
    {
        case 1:
            PlayerPosX = 14;
            PlayerPosY = 4;
            break;
        case 2:
            PlayerPosX = 13;
            PlayerPosY = 2;
            break;
        case 3:
            PlayerPosX = 14;
            PlayerPosY = 3;
            break;
        default:
            break;
    }
    loadPlayerImage();
    loadGoblinImages();
}
