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

    // parse and archive questions from questions.txt
    qManager = new QuestionManager;

    // create our model
    controller = new GameController;

    // populate our goblinLabelVector
    goblinLabelVector->push_back(ui->GoblinLabel1);
    goblinLabelVector->push_back(ui->GoblinLabel2);
    goblinLabelVector->push_back(ui->GoblinLabel3);
    goblinLabelVector->push_back(ui->GoblinLabel4);
    goblinLabelVector->push_back(ui->GoblinLabel5);

    // ensure answer line edit only accepts ints and is hidden
    ui->AnswerLineEdit->setValidator(new QIntValidator(-1000, 1000, this));
    ui->AnswerLineEdit->hide();
    // ensure parchment text label is hidden and parchment render label are hidden
    ui->ParchmentLabel->hide();
    ui->ParchmentTextLabel->hide();
    // ensure answer button is hidden
    ui->SubmitAnswerButton->hide();

    // CONNECTIONS
    connect(controller, SIGNAL(changeMapImageRequest(QImage*)), this, SLOT(changeMapImage(QImage*)));
    connect(controller, SIGNAL(changePlayerImageRequest(QImage*,int,int)), this, SLOT(changePlayerImage(QImage*,int,int)));
    connect(this, SIGNAL(moveRequested(std::string)), controller, SLOT(moveRequested(std::string)));
    connect(controller, SIGNAL(changeGoblinImageRequest(QImage*,int,int,int)), this, SLOT(changeGoblinImage(QImage*,int,int,int)));
    connect(controller, SIGNAL(killGoblin(int)), this, SLOT(killGoblin(int)));
    connect(controller, SIGNAL(showParchment(QString,bool,QImage*)), this, SLOT(showParchment(QString,bool,QImage*)));


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

// the slot used by the model to cause the parchment page to display
// takeAnswer determines if we are showing the player a question (true) or a hint (false)
void MainWindow::showParchment(QString textToDisplay, bool takeAnswer, QImage * parchmentImage)
{
    // calculate center of screen for later use
    int centerX = ui->centralWidget->size().width()/2;
    int centerY = ui->centralWidget->size().height()/2;

    // if take answer, show the answer line edit, else we are just showing the player a hint
    if (takeAnswer)
    {
        ui->SubmitAnswerButton->setText(QString("Submit Answer"));

        ui->AnswerLineEdit->move(centerX - ui->AnswerLineEdit->size().width()/2, centerY*1.5);
        ui->AnswerLineEdit->show();
    }

    else
    {
        ui->SubmitAnswerButton->setText(QString("Ok"));
    }

    // set the parchment image and format correctly
    ui->ParchmentLabel->setMaximumSize(parchmentImage->size());
    ui->ParchmentLabel->setMinimumSize(parchmentImage->size());
    ui->ParchmentLabel->setPixmap(QPixmap::fromImage(*parchmentImage));

    // set the parchment text we want to display and set its size
    ui->ParchmentTextLabel->setText(textToDisplay);
    ui->ParchmentTextLabel->setMinimumSize(parchmentImage->size()/2);

    // move all the widgets to the center of the screen formatted correctly
    ui->ParchmentLabel->move(centerX - ui->ParchmentLabel->size().width()/2, centerY - ui->ParchmentLabel->size().height()/2 + 20);
    ui->ParchmentTextLabel->move(centerX - ui->ParchmentTextLabel->size().width()/2, centerY*.6);
    ui->SubmitAnswerButton->move(centerX - ui->SubmitAnswerButton->size().width()/2, centerY * 1.4);

    // show all widgets
    ui->ParchmentLabel->show();
    ui->ParchmentTextLabel->show();
    ui->SubmitAnswerButton->show();

    // set focus on the submit answer button to make sure the player cannot move
    ui->SubmitAnswerButton->setFocus();
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

// event handler for when the submit answer button is clicked
void MainWindow::on_SubmitAnswerButton_clicked()
{
    // hide all the UI elements for the Question
    ui->SubmitAnswerButton->hide();
    ui->ParchmentLabel->hide();
    ui->ParchmentTextLabel->hide();
    ui->AnswerLineEdit->hide();

    // get the answer out of the Answer Line Edit and send it to the model and clear it
    QString answer = ui->AnswerLineEdit->text();
    emit answerSubmitted(answer.toInt());
    ui->AnswerLineEdit->clear();

    // give focus back to central widget
    ui->centralWidget->setFocus();
}
