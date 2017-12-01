#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>

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

signals:
    void changeMapImageRequest(QImage * image);
    void changePlayerImageRequest(QImage * image, int x, int y);

public slots:
    void moveRequested(std::string movement);

private:
    // variables to keep track of the current game state
    int PlayerPosX = 0;
    int PlayerPosY = 0;

    // the QImage we use to store the map
    QImage * mapImage;
    // the QImages we use to store the player sprites (organized front, back, left, right for the direction they face)
    QImage * playerSprite_f;
    QImage * playerSprite_b;
    QImage * playerSprite_l;
    QImage * playerSprite_r;
    char lastMoveDirection = 'f'; // tells us what playerImage to send to the view. Assigned during movement
    // the size of the grid in pixels and it's total number of grid units in x and z
    int gridRatio = 40;
    int maxGridSizeY = 16;
    int maxGridSizeX = 16;
    // a vector of std::pairs of collision points for the player
    std::vector<std::pair<int, int>> * collisionPoints = new std::vector<std::pair<int, int>>();

    // the method called to emit a signal for the view to move the player
    movePlayer(std::string movement);
};


#endif // GAMECONTROLLER_H
