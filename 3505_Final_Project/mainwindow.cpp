#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <iostream>

// Constructor for main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create our model
    controller = new GameController;

    // populate our goblinLabelVector
    goblinLabelVector->push_back(ui->GoblinLabel1);
    goblinLabelVector->push_back(ui->GoblinLabel2);
    goblinLabelVector->push_back(ui->GoblinLabel3);
    goblinLabelVector->push_back(ui->GoblinLabel4);
    goblinLabelVector->push_back(ui->GoblinLabel5);

    // CONNECTIONS
    connect(controller, SIGNAL(changeMapImageRequest(QImage*)), this, SLOT(changeMapImage(QImage*)));
    connect(controller, SIGNAL(changePlayerImageRequest(QImage*,int,int)), this, SLOT(changePlayerImage(QImage*,int,int)));
    connect(this, SIGNAL(moveRequested(std::string)), controller, SLOT(moveRequested(std::string)));
    connect(controller, SIGNAL(changeGoblinImageRequest(QImage*,int,int,int)), this, SLOT(changeGoblinImage(QImage*,int,int,int)));
    connect(controller, SIGNAL(killGoblin(int)), this, SLOT(killGoblin(int)));


    // tell the controller to load the map
    controller->loadMapImage();
    // move the player to their start position
    controller->loadPlayerImage();
    // load any goblins in the scene
    controller->loadGoblinImages();
}

// destructor for main window
MainWindow::~MainWindow()
{
    delete ui;
}

// CUSTOM SLOTS - FROM MODEL
// the slot used to change the Map Image displayed on the screen
void MainWindow::changeMapImage(QImage *newImage)
{
    ui->MapLabel->setMaximumSize(newImage->size());
    ui->MapLabel->setMinimumSize(newImage->size());
    ui->MapLabel->setPixmap(QPixmap::fromImage(*newImage));
    ui->MapLabel->show();
    ui->centralWidget->setMinimumSize(newImage->size() + QSize(40, 0));
}
// the slot used to change the image and location of the image of the player on the screen
void MainWindow::changePlayerImage(QImage *image, int x, int y)
{
    ui->PlayerLabel->setMaximumSize(image->size());
    ui->PlayerLabel->setMinimumSize(image->size());
    ui->PlayerLabel->setPixmap(QPixmap::fromImage(*image));
    ui->PlayerLabel->move(x, y);
    ui->PlayerLabel->show();
}

// the slot used to change the image and location of the image of a goblin on the screen
void MainWindow::changeGoblinImage(QImage *image, int x, int y, int i)
{
    goblinLabelVector->at(i)->setMaximumSize(image->size());
    goblinLabelVector->at(i)->setMinimumSize(image->size());
    goblinLabelVector->at(i)->setPixmap(QPixmap::fromImage(*image));
    goblinLabelVector->at(i)->move(x, y);
    goblinLabelVector->at(i)->show();
}

// the slot that will remove the goblins label from the goblinLabelVector
void MainWindow::killGoblin(int i)
{
    //goblinLabelVector->pop_back();
}

// QT GENERATED SLOTS - FROM VIEW
// this is an event handler for Key Presses
void MainWindow::keyPressEvent(QKeyEvent *KeyEvent)
{
    // first check if the event is the result of someone holding down a key. If it is,
    // ignore the event because we do not care.
    if (KeyEvent->isAutoRepeat())
    {
        return;
    }

    // this is a temporary debug feature to show us the key that was pressed
    // std::cout << KeyEvent->text().toUtf8().data() << " Was Pressed" << std::endl;

    // This section fires the relevant event to the model based on the key pressed
    // This is where controls are configured.
    QString keyText = KeyEvent->text();
    keyText = keyText.toLower();
    if (keyText == "w")
    {
        emit moveRequested(std::string("UP"));
    }
    else if (keyText == "s")
    {
        emit moveRequested(std::string("DOWN"));
    }
    else if (keyText == "d")
    {
        emit moveRequested(std::string("RIGHT"));
    }
    else if (keyText == "a")
    {
        emit moveRequested(std::string("LEFT"));
    }
}
