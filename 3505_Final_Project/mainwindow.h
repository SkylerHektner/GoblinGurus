#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // container for our GameController Model
    GameController * controller;

signals:
    moveRequested(std::string movement);

public slots:
    void changeMapImage(QImage * newImage);
    void changePlayerImage(QImage * image, int x, int y);
    void changeGoblinImage(QImage * image, int x, int y, int i);
    void killGoblin(int i);

private:
    Ui::MainWindow *ui;

    // A vector of Labels used to render the goblins in the scene
    std::vector<QLabel*> * goblinLabelVector = new std::vector<QLabel*>();

    // listens for key press events and fires when one is recieved
    void keyPressEvent(QKeyEvent * KeyEvent);
};

#endif // MAINWINDOW_H
