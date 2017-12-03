#include "question.h"

Question::Question(int an, int ti, std::string te)
{
    answer = an;
    tier = ti;
    text = te;
}

Question::~Question()
{

}

Question::Question(const Question &other)
{
    answer = other.answer;
    text = other.text;
    tier = other.tier;
}

