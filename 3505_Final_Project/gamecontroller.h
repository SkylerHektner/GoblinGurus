#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>
#include "goblin.h"

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

signals:
    void changeMapImageRequest(QImage * image);
    void changePlayerImageRequest(QImage * image, int x, int y);

    // in the two below methods, i refers to the index of the goblin we want to act on
    void changeGoblinImageRequest(QImage * image, int x, int y, int i);
    void killGoblin(int i);

public slots:
    void moveRequested(std::string movement);

private:
    // variables to keep track of the current game state
    int PlayerPosX = 0;
    int PlayerPosY = 0;

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
    // the size of the grid in pixels and it's total number of grid units in x and z
    int gridRatio = 80;
    int maxGridSizeY = 9;
    int maxGridSizeX = 15;
    int gridOffsetX = 40;
    int gridOffsetY = 40;
    // a vector of std::pairs of collision points for the player
    std::vector<std::pair<int, int>> * collisionPoints = new std::vector<std::pair<int, int>>();

    // a vector of the goblins on the map
    std::vector<goblin*> * goblinVector = new std::vector<goblin*>();

    // the method called to emit a signal for the view to move the player
    movePlayer(std::string movement);
};


#endif // GAMECONTROLLER_H
