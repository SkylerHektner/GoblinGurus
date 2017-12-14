#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gamecontroller.h"
#include "questionmanager.h"
#include "effect.h"
#include <QLabel>
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QuestionManager * qManager;

    // container for our GameController Model
    GameController * controller;

signals:
    void moveRequested(std::string movement);
    void answerSubmitted(int answer);

public slots:
    void changeMapImage(QImage * newImage);
    void changePlayerImage(QImage * image, int x, int y);
    void changeGoblinImage(QImage * image, int x, int y, int i);
    void killGoblin(int i);
    void showParchment(QString textToDisplay, bool takeAnswer, QImage * parchmentImage);
    void updateHealth(QString health);
    void startGame(int difficulty);
    void michaelBay(int x, int y);

private slots:
    void on_SubmitAnswerButton_clicked();
    void updateWorld();

private:
    Ui::MainWindow *ui;

    // A vector of Labels used to render the goblins in the scene
    std::vector<QLabel*> * goblinLabelVector = new std::vector<QLabel*>();

    // listens for key press events and fires when one is recieved
    void keyPressEvent(QKeyEvent * KeyEvent);
    //Physics stuff
    //create dynamic bodies
    void createBox(b2World &world, float posX, float posY);
    //some ground
    void createGround(b2World &world, float posX, float posY);
    //help michaelBay make some explosions
    void makeExplodingGoblin(int, int);
    float scale;
    QTimer* timer;
    effect *_effect;
    sf::Texture body;
    sf::Texture hand;
};

#endif // MAINWINDOW_H
