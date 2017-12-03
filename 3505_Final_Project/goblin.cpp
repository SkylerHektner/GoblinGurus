
#include "goblin.h"
#include <iostream>

goblin::goblin(int x, int y, std::string questionText, int answer)
{
    posX = x;
    posY = y;
    question = QString(questionText.c_str());
    answer = answer;
    goblinSprite = new QImage("../Assets/spr_goblin_sword.png");
    goblinSprite ->setDevicePixelRatio(1);
}

goblin::~goblin()
{
    delete goblinSprite;
}
