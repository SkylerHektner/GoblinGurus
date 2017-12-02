#ifndef QUESTIONMANAGER_H
#define QUESTIONMANAGER_H
#include <iostream>
#include <list>
#include <vector>
#include "question.h"

class QuestionManager
{
public:
    unsigned tierCount;
    std::vector<std::vector<Question>> questions;

    QuestionManager();
    ~QuestionManager();

    // retrieves a random question from the requested tier
    Question GetQuestion(int tier);

private:
    void ParseQuestion(std::string line);

};

#endif // QUESTIONMANAGER_H
