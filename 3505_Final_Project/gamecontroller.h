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

signals:
    void changeMapImageRequest(QImage * image);

public slots:

private:
    // variables to keep track of the current game state
    int PlayerPosX = 0;
    int PlayerPoxY = 0;

    // the QImage we use to store the map
    QImage * mapImage;
    // the size of the grid in pixels
    int gridSize = 10;



    // the method called to move the player
    movePlayer(std::string movement);
};


#endif // GAMECONTROLLER_H
