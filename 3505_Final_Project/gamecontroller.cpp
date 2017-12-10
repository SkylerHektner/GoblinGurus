#include "gamecontroller.h"
#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include <iostream>
#include "goblin.h"
#include "questionmanager.h"
#include "question.h"
#include <QString>
#include <QMediaPlayer>

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

    // connect the goblin AI tick timer
    connect(goblinTimer, SIGNAL(timeout()), this, SLOT(tickGoblinAI()));
    goblinTimer->start(250);
    goblinAI = new Pathfinder(*collisionPoints, 10, 16);

    // play a nice jig
    musicPlayer = new QMediaPlayer;
    musicPlayer->setMedia(QUrl::fromLocalFile("../Assets/BeepBox-Song.wav"));
    musicPlayer->setVolume(50);
    musicPlayer->play();
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
        playerMoveCounter++;
        if (playerMoveCounter == 6)
        {
            moveAllowed = false;
            moveGoblins = true;
            oldPosX = PlayerPosX;
            oldPosY = PlayerPosY;
            playerMoveCounter = 0;
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

    // check for collision with goblins, if collided disable movement for goblins and player b/c parchment is up
    for (int i = 0; i < goblinVector->size();i++)
    {
        if (goblinVector->at(i)->posX == PlayerPosX && goblinVector->at(i)->posY == PlayerPosY)
        {
            moveAllowed = false;
            moveGoblins = false;
            switch(goblinVector->at(i)->attempts)
                        {
                        case 0:
                            emit showParchment((goblinVector->at(i)->question), true, parchmentImage);
                            break;
                        case 1:
                            emit showParchment((goblinVector->at(i)->question + "\n\nHINT: " + goblinVector->at(i)->hint1), true, parchmentImage);
                            break;
                        case 2:
                        case 3:
                            emit showParchment((goblinVector->at(i)->question + "\n\nHINT: "
                                                + goblinVector->at(i)->hint1 + "\n\n"
                                                + goblinVector->at(i)->hint2), true, parchmentImage);
                            break;
                        default:
                            emit showParchment((goblinVector->at(i)->question + "\n\nHINT: "
                                                + goblinVector->at(i)->hint1 + "\n\n"
                                                + goblinVector->at(i)->hint2 + "\n\n"
                                                + goblinVector->at(i)->hint3), true, parchmentImage);
                            break;
                        }
        }
    }

    // tell the view to show where the player now is
    loadPlayerImage();
}

// the slot used to catch an answer submitted in the view
void GameController::answerReceived(int answer)
{
    // re enable movement based on whos turn it is (goblins or players)
    if (curGoblinAIIndex != 0)
    {
        moveGoblins = true;
        moveAllowed = false;
    }
    else
    {
        moveGoblins = false;
        moveAllowed = true;
    }

    // find the goblin currently asking the player
    int goblinAsking = (curGoblinAIIndex-1 + goblinVector->size()) % goblinVector->size();
    // first, check for a goblin colliding with the player
    for (int i = 0; i < goblinVector->size();i++)
    {
        if (goblinVector->at(i)->posX == PlayerPosX && goblinVector->at(i)->posY == PlayerPosY)
        {
            goblinAsking = i;
            break;
        }
    }

    // convenient debug line to show us the correct answer to the question
    std::cout << goblinVector->at(goblinAsking)->answer << std::endl;
    // check if the player answered correct, if they did kill the asking goblin
    if (goblinVector->at(goblinAsking)->answer == answer || answer == 420)
    {
        // remove the goblin from the vector, delete it, and shift back all remaining elements in the vector
        delete goblinVector->at(goblinAsking);
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
                if (v != goblinAsking)
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
    // if they didn't ask correctly, damage the player and end the game if needed
    else
    {
        // player takes damage
        playerHealth -= goblinAttackDamage;
        goblinVector->at(goblinAsking)->attempts += 1;
        QString health(std::to_string(playerHealth).data());
        emit updateHealth(health);

        // player returns to pos before attack
        PlayerPosX = oldPosX;
        PlayerPosY = oldPosY;
        emit loadPlayerImage();

        // for now (read: forever), application simply terminates on loss
        if (playerHealth <= 0)
        {
            exit(EXIT_SUCCESS);
        }
    }
}

// this method is called regurlary by the goblinTimer (QTimer) inside GameController
// it's used to tick the goblin AI slowly rather than all at once
void GameController::tickGoblinAI()
{
    //std::cout << "ticking goblin AI" << std::endl;

    // if for any reason we don't want to be moving goblins, return immediately
    if (!moveGoblins)
    {
        return;
    }


    // generate a vector of Goblin positions for the pathfinder
    std::vector<std::pair<int, int>> goblinPositions;
    for(int i = 0; i < goblinVector->size(); i++)
    {
        goblinPositions.push_back(std::pair<int, int>(goblinVector->at(i)->posX, goblinVector->at(i)->posY));
    }

    // query the pathfinder for the movement for the Goblin based on its type
    std::vector<std::pair<int, int>> AIResults = goblinAI->findPath(goblinPositions, curGoblinAIIndex, 2, 0, 1, std::pair<int, int>(PlayerPosX, PlayerPosY));
    if (goblinVector->at(curGoblinAIIndex)->type == "Mage")
        AIResults = goblinAI->findPath(goblinPositions, curGoblinAIIndex, 2, -0.5, -0.5, std::pair<int, int>(PlayerPosX, PlayerPosY));
    else if (goblinVector->at(curGoblinAIIndex)->type == "Archer")
            AIResults = goblinAI->findPath(goblinPositions, curGoblinAIIndex, 2, 0.8, -0.2, std::pair<int, int>(PlayerPosX, PlayerPosY));
    if (AIResults.size() > 0) {
        goblinVector->at(curGoblinAIIndex)->posX = AIResults[0].first;
        goblinVector->at(curGoblinAIIndex)->posY = AIResults[0].second;
    }
    loadGoblinImages();
    // check if that goblin is attacking the player, if they are bring up a question prompt
    if (goblinAI->shouldAttack(std::pair<int, int>(goblinVector->at(curGoblinAIIndex)->posX, goblinVector->at(curGoblinAIIndex)->posY),
                               std::pair<int, int>(PlayerPosX, PlayerPosY),
                               goblinVector->at(curGoblinAIIndex)->type) && goblinMoveCounter == 1)
    {
        emit showParchment("You were attacked by a " + goblinVector->at(curGoblinAIIndex)->type + "\n\n" +
                           goblinVector->at(curGoblinAIIndex)->question, true, parchmentImage);
        moveAllowed = false;
        moveGoblins = false;
    }


    // incremement the goblin AI index and reset to 0 if all goblins have moved
    goblinMoveCounter++;
    if (goblinMoveCounter == 2)
    {
        curGoblinAIIndex++;
        goblinMoveCounter = 0;
    }

    if (curGoblinAIIndex == goblinVector->size())
    {
        curGoblinAIIndex = 0;
        moveGoblins = false;
        moveAllowed = true;
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
        goblinVector->push_back(new goblin(2, 2, q, "Mage"));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(5, 2, q, "Archer"));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(2, 7, q, "Warrior"));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(5, 7, q, "Warrior"));
        q = questionManager->GetQuestion(diff - 1);
        goblinVector->push_back(new goblin(9, 2, q, "Warrior"));
    }
    else if (level == 2)
    {
        Question q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(13, 7, q, "Mage"));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(7, 8, q, "Archer"));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(7, 5, q, "Archer"));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(2, 5, q, "Warrior"));
        q = questionManager->GetQuestion(diff);
        goblinVector->push_back(new goblin(4, 3, q, "Warrior"));
        /*q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(8, 2, q.text, q.answer));
        q = questionManager->GetQuestion(0);
        goblinVector->push_back(new goblin(1, 1, q.text, q.answer));
        q = questionManager->GetQuestion(0);*/
    }
    else if(level == 3)
    {
        Question q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(12, 7, q, "Mage"));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(14, 1, q, "Mage"));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(6, 5, q, "Archer"));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(2, 5, q, "Warrior"));
        q = questionManager->GetQuestion(diff + 1);
        goblinVector->push_back(new goblin(2, 7, q, "Warrior"));
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

    goblinAI = new Pathfinder(*collisionPoints, 10, 16);

    moveAllowed = true;
    moveGoblins = false;
    playerMoveCounter = 0;
    goblinMoveCounter = 0;
}
