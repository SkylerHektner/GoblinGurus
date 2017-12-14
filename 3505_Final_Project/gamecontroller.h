#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>
#include "goblin.h"
#include "questionmanager.h"

/*
 * This class is the primary model object for the game. It ultimately is responsible for interfacing with the view.
 * Subclasses can and should be used for game logic, but all signals to the view (mainwindow.h) should come from here
 */
class GameController: public QObject
{
    Q_OBJECT

public:
    ~GameController(); // destructor
    explicit GameController(QObject * parent = 0);

    void loadMapImage();
    void loadPlayerImage();
    void loadGoblinImages();
    int diff;
    void startGame();

signals:
    void changeMapImageRequest(QImage * image);
    void changePlayerImageRequest(QImage * image, int x, int y);
    void showParchment(QString QuestionText, bool takeAnswer, QImage * image);
    void updateHealth(QString health);

    // in the two below methods, i refers to the index of the goblin we want to act on
    void changeGoblinImageRequest(QImage * image, int x, int y, int i);
    void killGoblin(int i);
    // call michaelBay to explode some goblins.
    void michaelBay(int, int);

public slots:
    void moveRequested(std::string movement);
    void answerReceived(int answer);

private:

    int goblinAttackDamage = 10;
    // player attack: OP AS FUUUUUCCCKKKKK

    // variables to keep track of the current game state
    int PlayerPosX = 0;
    int PlayerPosY = 0;
    int oldPosX = 0;
    int oldPosY = 0;

    // current level, starts at level 1
    int level = 1;

    // player health
    int playerHealth = 100;

    // the QImage we use to store the map
    QImage * mapImage;
    // the QImage we use to store the parchment paper used in questions and hints
    QImage * parchmentImage;
    // the QImages we use to store the player sprites (organized front, back, left, right for the direction they face)
    QImage * playerSprite_f;
    QImage * playerSprite_b;
    QImage * playerSprite_l;
    QImage * playerSprite_r;
    char lastMoveDirection = 'f'; // tells us what playerImage to send to the view. Assigned during movement
    bool moveAllowed = true; // used to determine if the player is allowed to move currently
    // the size of the grid in pixels and it's total number of grid units in x and z
    int gridRatio = 80;
    int maxGridSizeY = 9;
    int maxGridSizeX = 15;
    int gridOffsetX = 40; // used to account for map borders or other
    int gridOffsetY = 40; // used to account for map borders or other
    // a vector of std::pairs of collision points for the player
    std::vector<std::pair<int, int>> * collisionPoints = new std::vector<std::pair<int, int>>();

    // a vector of the goblins on the map
    std::vector<goblin*> * goblinVector = new std::vector<goblin*>();

    // the question manager
    QuestionManager * questionManager = new QuestionManager();

    // the method called to emit a signal for the view to move the player
    void movePlayer(std::string movement);

    // populates the collision vector with the proper points given the level
    void generateLevelCollisionPoints();
    // populates the goblins vector with the proper goblins given the level
    void generateGoblins();
    void generateNextLevel();
};


#endif // GAMECONTROLLER_H
