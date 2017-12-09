#include "question.h"
#include "goblin.h"
#include <iostream>

goblin::goblin(int x, int y, Question q)
{
    posX = x;
    posY = y;
    question = QString::fromStdString(q.text);
    answer = q.answer;
    hint1 = QString::fromStdString(q.hint1);
    hint2 = QString::fromStdString(q.hint2);
    hint3 = QString::fromStdString(q.hint3);
    goblinSprite = new QImage("../Assets/spr_goblin_sword.png");
    goblinSprite ->setDevicePixelRatio(1);
}

goblin::~goblin()
{
    delete goblinSprite;
}
