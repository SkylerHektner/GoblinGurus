#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include "questionmanager.h"
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
    void startGame(int difficulty);

private slots:
    void on_SubmitAnswerButton_clicked();

private:
    Ui::MainWindow *ui;

    // A vector of Labels used to render the goblins in the scene
    std::vector<QLabel*> * goblinLabelVector = new std::vector<QLabel*>();

    // listens for key press events and fires when one is recieved
    void keyPressEvent(QKeyEvent * KeyEvent);
};

#endif // MAINWINDOW_H
