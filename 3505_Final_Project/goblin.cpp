
#include "goblin.h"
#include <iostream>

goblin::goblin(int x, int y, std::string question, int answer)
{
    posX = x;
    posY = y;
    question = question;
    answer = answer;
    goblinSprite = new QImage("../Assets/spr_goblin_sword.png");
    goblinSprite ->setDevicePixelRatio(1);
}

goblin::~goblin()
{
    delete goblinSprite;
}
