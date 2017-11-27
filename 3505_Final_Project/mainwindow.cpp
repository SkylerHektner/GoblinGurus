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

    // CONNECTIONS
    connect(controller, SIGNAL(changeMapImageRequest(QImage*)), this, SLOT(changeMapImage(QImage*)));


    // tell the controller to load the map
    controller->loadMapImage();
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
    //std::cout << KeyEvent->text().toUtf8().data() << " Was Pressed" << std::endl;

    // This section fires the relevant event to the model based on the key pressed
    // This is where controls are configured.
    QString keyText = KeyEvent->text();
    keyText = keyText.toLower();
    if (keyText == "w")
    {
        emit moveRequested("UP");
    }
    else if (keyText == "s")
    {
        emit moveRequested("DOWN");
    }
    else if (keyText == "d")
    {
        emit moveRequested("RIGHT");
    }
    else if (keyText == "a")
    {
        emit moveRequested("LEFT");
    }
}
