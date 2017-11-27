#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>

/*
 * This class is the primary model object for the game. It ultimately is responsible for interfacing with the view.
 * Subclasses can and should be used for game logic, but all signals to the view (mainwindow.h) should come from here
 */
class GameController
{

public:
    ~GameController(); // destructor
    GameController(); // constructor

signals:

public slots:

private:

};


#endif // GAMECONTROLLER_H
