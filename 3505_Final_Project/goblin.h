#ifndef GOBLIN_H
#define GOBLIN_H

#include <iostream>
#include <QImage>

class goblin
{
public:
    goblin(int x, int y, std::string questionText, int answer);
    ~goblin();

    // Position
    int posX = 0;
    int posY = 0;
    int attempts = 0;
    // question and answer
    QString question;
    int answer;
    // sprites
    QImage * goblinSprite;

private:

};

#endif // GOBLIN_H
