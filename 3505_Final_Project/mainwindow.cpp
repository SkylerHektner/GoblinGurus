#include "mainwindow.h"
#include "difficultyselector.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include "pathfinder.h"
#include <QString>
#include "effect.h"

void testPathfind(int, int);
void removeBodies(b2Body &body);
bool addToDelete = true;
void createWalls();
QVector<b2Body *> bodiesToDestroy;
b2Vec2 gravity(0.0f, 2.5f);
b2World world(gravity);
// Constructor for main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Create effects physics
    scale = 30;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWorld);
    timer->start(33);
    //create the sprite (effect) class
    _effect = new effect();
    //create the outer walls
    createWalls(world);
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

    ui->Health->move(60,20);

    // CONNECTIONS
    connect(controller, SIGNAL(changeMapImageRequest(QImage*)), this, SLOT(changeMapImage(QImage*)));
    connect(controller, SIGNAL(changePlayerImageRequest(QImage*,int,int)), this, SLOT(changePlayerImage(QImage*,int,int)));
    connect(this, SIGNAL(moveRequested(std::string)), controller, SLOT(moveRequested(std::string)));
    connect(controller, SIGNAL(showParchment(QString,bool,QImage*)), this, SLOT(showParchment(QString,bool,QImage*)));
    connect(controller, SIGNAL(updateHealth(QString)), this, SLOT(updateHealth(QString)));
    connect(controller, SIGNAL(changeGoblinImageRequest(QImage*,int,int,int)), this, SLOT(changeGoblinImage(QImage*,int,int,int)));
    connect(controller, SIGNAL(killGoblin(int)), this, SLOT(killGoblin(int)));
    connect(this, SIGNAL(answerSubmitted(int)), controller, SLOT(answerReceived(int)));
    connect(controller, SIGNAL(michaelBay(int,int)), this, SLOT(michaelBay(int,int)));

    difficultyselector * selector = new difficultyselector;
    connect(selector, SIGNAL(playGame(int)), this, SLOT(startGame(int)));
    selector->setModal(true);
    selector->exec();
}

void MainWindow::startGame(int difficulty)
{
    controller->diff = difficulty;
    controller->startGame();
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
    //destroyWalls(world);
    ui->MapLabel->setMaximumSize(newImage->size());
    ui->MapLabel->setMinimumSize(newImage->size());
    ui->MapLabel->setPixmap(QPixmap::fromImage(*newImage));
    ui->MapLabel->show();
    ui->centralWidget->setMinimumSize(newImage->size() + QSize(0, 0));
    createWalls(world);
}
// the slot used to change the image and location of the image of the player on the screen
void MainWindow::changePlayerImage(QImage *image, int x, int y)
{
    ui->PlayerLabel->setMaximumSize(image->size());
    ui->PlayerLabel->setMinimumSize(image->size());
    ui->PlayerLabel->setPixmap(QPixmap::fromImage(*image));
    ui->PlayerLabel->move(x, y);
    ui->PlayerLabel->show();
    //testPathfind((x-20)/80, (y-20)/80);
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
    goblinLabelVector->at(i)->setPixmap(QPixmap());
    goblinLabelVector->at(i)->show();
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
    ui->ParchmentTextLabel->setMinimumSize(parchmentImage->size()/4);
    ui->ParchmentTextLabel->setMaximumSize(parchmentImage->size()/4);

    // move all the widgets to the center of the screen formatted correctly
    ui->ParchmentLabel->move(centerX - ui->ParchmentLabel->size().width()/2, centerY - ui->ParchmentLabel->size().height()/2);
    ui->ParchmentTextLabel->move(centerX - ui->ParchmentTextLabel->size().width()/2, centerY*.6);
    ui->SubmitAnswerButton->move(centerX - ui->SubmitAnswerButton->size().width()/2, centerY * 1.4);

    // show all widgets
    ui->ParchmentLabel->show();
    ui->ParchmentTextLabel->show();
    ui->SubmitAnswerButton->show();

    // set focus on the submit answer button to make sure the player cannot move
    ui->SubmitAnswerButton->setFocus();
}

void MainWindow::updateHealth(QString health)
{
    ui->Health->setText(QString("Health: ") + health);
    ui->Health->move(60,20);
    ui->Health->show();
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

void testPathfind(int x, int y) {
    std::vector<std::pair<int, int>> collisionPoints;

    // create border points
    for(int i = 0; i < 16; i++)
    {
        collisionPoints.push_back(std::pair<int, int>(i, 0));
        collisionPoints.push_back(std::pair<int, int>(i, 9));
    }
    for(int i = 0; i < 10; i++)
    {
        collisionPoints.push_back(std::pair<int, int>(0, i));
        collisionPoints.push_back(std::pair<int, int>(15, i));
    }

    // define level 1 inner walls
    collisionPoints.push_back(std::pair<int, int>(1, 4));
    collisionPoints.push_back(std::pair<int, int>(1, 5));
    collisionPoints.push_back(std::pair<int, int>(3, 4));
    collisionPoints.push_back(std::pair<int, int>(3, 5));
    collisionPoints.push_back(std::pair<int, int>(4, 4));
    collisionPoints.push_back(std::pair<int, int>(4, 5));
    collisionPoints.push_back(std::pair<int, int>(6, 4));
    collisionPoints.push_back(std::pair<int, int>(6, 5));
    collisionPoints.push_back(std::pair<int, int>(7, 1));
    collisionPoints.push_back(std::pair<int, int>(7, 3));
    collisionPoints.push_back(std::pair<int, int>(7, 4));
    collisionPoints.push_back(std::pair<int, int>(7, 5));
    collisionPoints.push_back(std::pair<int, int>(7, 6));
    collisionPoints.push_back(std::pair<int, int>(7, 7));
    collisionPoints.push_back(std::pair<int, int>(7, 8));
    collisionPoints.push_back(std::pair<int, int>(10, 3));
    collisionPoints.push_back(std::pair<int, int>(10, 6));
    collisionPoints.push_back(std::pair<int, int>(11, 2));
    collisionPoints.push_back(std::pair<int, int>(11, 3));
    collisionPoints.push_back(std::pair<int, int>(11, 6));
    collisionPoints.push_back(std::pair<int, int>(11, 7));
    collisionPoints.push_back(std::pair<int, int>(12, 3));
    collisionPoints.push_back(std::pair<int, int>(12, 6));

    Pathfinder pathfinder(collisionPoints, 10, 16);

    std::vector<std::pair<int, int>> enemies;
    enemies.push_back(std::pair<int, int>(9, 2));

    std::pair<int, int> playerPosition(x, y);
    pathfinder.findPath(enemies, 0, 4, 0, 1, playerPosition);
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

void MainWindow::updateWorld(){
int BodyCount = 0;
world.Step(1/30.0f, 8, 3);
for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator->GetType() == b2_dynamicBody)
        {
            //For sprite background transform.
            _effect->moveEffect(BodyCount, BodyIterator->GetAngle() * 180/b2_pi, scale * BodyIterator->GetPosition().x, scale * BodyIterator->GetPosition().y);
            ++BodyCount;
        }
        qDebug() << world.GetBodyCount();
        //remvoe the body if it is off screen.
        if((scale * BodyIterator->GetPosition().y) > 3000){
            removeBodies(*BodyIterator);
            qDebug() << world.GetBodyCount();
            return;
        }
    }
}

void MainWindow::michaelBay(int x, int y)
{
    makeExplodingGoblin(x, y);
}

void MainWindow::makeExplodingGoblin(int goblinX, int goblinY){
    //add goblin to effect
    float boxSize = 10.0f; //size of the box depending on the asset loaded
    if(body.loadFromFile("../Assets/BODY.png")){}
    if(hand.loadFromFile("../Assets/HAND.png")){}
    QVector<sf::Texture> imagePTRs;
    for(int i = 0; i < 15; i++){
        if(i < 5){
            imagePTRs.append(body);
            boxSize = body.getSize().x;
        }
        else{
            imagePTRs.append(hand);
            boxSize = body.getSize().x;
        }
        //Make bodies
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(goblinX/scale, goblinY/scale); //need to scale the pixel positions to real world positions. World is in meters
        BodyDef.type = b2_dynamicBody;
        b2Body* Body = world.CreateBody(&BodyDef);
        if(true) {Body->ApplyLinearImpulse(b2Vec2( qrand()%5,  -qrand()%3), Body->GetWorldCenter(), true);}
        b2PolygonShape Shape;
        Shape.SetAsBox((boxSize/2)/scale, (boxSize/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }
    _effect->addSprite(imagePTRs, this);
}

void MainWindow::createWalls(b2World &world){
    //top wall
    {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2((1360/2)/scale, 0);
    BodyDef.type = b2_staticBody;
    b2Body* Body = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((1360.0f)/scale, 0);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    }
    //create obsticles for the 1st level
    //
//    {
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2((80*12)/scale, (80*3)/scale);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = world.CreateBody(&BodyDef);
//    b2PolygonShape Shape;
//    Shape.SetAsBox((80.0f)/scale, (80.0)/scale);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);
//    }

    {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2((80*11)/scale, (80*4)/scale);
    BodyDef.type = b2_staticBody;
    b2Body* Body = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((40.0f)/scale, (40.0)/scale);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    }

}
void removeBodies(b2Body &body){
    world.DestroyBody(&body);
}
