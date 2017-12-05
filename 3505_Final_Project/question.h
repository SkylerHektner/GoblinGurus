#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>

struct Question
{
public:
    Question(int answer, int tier, std::string text, std::string hint1, std::string hint2, std::string hint3);
    ~Question();
    Question(const Question &other);

    int answer;
    int tier;
    std::string text;
    std::string hint1;
    std::string hint2;
    std::string hint3;

};


#endif // QUESTION_H
