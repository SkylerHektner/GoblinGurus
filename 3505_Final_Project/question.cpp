#include "question.h"

Question::Question(int an, int ti, std::string te, std::string _hint1, std::string _hint2, std::string _hint3)
{
    answer = an;
    tier = ti;
    text = te;
    hint1 = _hint1;
    hint2 = _hint2;
    hint3 = _hint3;
}

Question::~Question()
{

}

Question::Question(const Question &other)
{
    answer = other.answer;
    text = other.text;
    tier = other.tier;
    hint1 = other.hint1;
    hint2 = other.hint2;
    hint3 = other.hint3;
}

