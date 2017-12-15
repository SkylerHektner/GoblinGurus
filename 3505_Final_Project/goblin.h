#ifndef GOBLIN_H
#define GOBLIN_H

#include "question.h"
#include <iostream>
#include <QImage>

class goblin
{
public:
    goblin(int x, int y, Question q, QString t);
    ~goblin();

    // Position
    int posX = 0;
    int posY = 0;
    int attempts = 0;
    // question and answer
    QString question;
    QString hint1;
    QString hint2;
    QString hint3;
    QString type;
    int answer;
    // sprites
    QImage * goblinSprite;

private:

};

#endif // GOBLIN_H
