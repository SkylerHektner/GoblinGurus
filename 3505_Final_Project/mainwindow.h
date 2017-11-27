#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"

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
    moveRequested(char * movement);

public slots:
    void changeMapImage(QImage * newImage);

private:
    Ui::MainWindow *ui;



    // listens for key press events and fires when one is recieved
    void keyPressEvent(QKeyEvent * KeyEvent);
};

#endif // MAINWINDOW_H
