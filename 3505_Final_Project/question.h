#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>

struct Question
{
public:
    Question(int answer, int tier, std::string text);
    ~Question();
    Question(const Question &other);

    int answer;
    int tier;
    std::string text;

};


#endif // QUESTION_H
