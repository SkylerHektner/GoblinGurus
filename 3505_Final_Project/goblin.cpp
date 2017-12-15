#include "question.h"
#include "goblin.h"
#include <iostream>

goblin::goblin(int x, int y, Question q, QString t)
{
    posX = x;
    posY = y;
    question = QString::fromStdString(q.text);
    answer = q.answer;
    hint1 = QString::fromStdString(q.hint1);
    hint2 = QString::fromStdString(q.hint2);
    hint3 = QString::fromStdString(q.hint3);
    type = t;

    if (type == "Mage")
        goblinSprite = new QImage("../Assets/spr_mage_goblin.png");
    else if (type == "Archer")
        goblinSprite = new QImage("../Assets/spr_goblin_bow.png");
    else
        goblinSprite = new QImage("../Assets/spr_goblin_sword.png");



    goblinSprite ->setDevicePixelRatio(1);
}

goblin::~goblin()
{
    delete goblinSprite;
}
