#include "questionmanager.h"
#include "question.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <chrono>

QuestionManager::~QuestionManager()
{

}

QuestionManager::QuestionManager()
{
    // generate the question vectors for each tier
    tierCount = 6;
    for(unsigned i = 0; i < tierCount; i++)
    {
        std::vector<Question> tier;
        questions.push_back(tier);
    }

    // read from questions file and parse questions
    std::string line;
    std::ifstream file("questions.txt");

    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            ParseQuestion(line);
        }
    }
    else
    {
        std::cout << "could not open questions.txt file" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// expects a single question line with items split by the ';' delimiter
// splits this line by the delimiter and places each item in itemGroup by order of appearence
// these items are then used to contruct a question object.
// format: (answer);(tier);(question);(...);
void QuestionManager::ParseQuestion(std::string line)
{
    std::string item;
    std::vector<std::string> itemGroup;

    // line.length() - 2 because we don't care to capture "/n"
    for(unsigned i = 0; i < line.length(); i++)
    {
        if(line[i] != ';')
        {
            item += line[i];
        }
        // we've reached a delimiter, add the item, clear item, and continue
        else
        {
            if(item != "/n")
            {
                itemGroup.push_back(item);
            }
            item = "";
        }
    }

    // convert values that are stored as int
    int answer;
    int tier;
    answer = std::stoi(itemGroup.at(0));
    tier = std::stoi(itemGroup.at(1)) - 1;

    Question question(answer, tier, itemGroup.at(2), itemGroup.at(3), itemGroup.at(4), itemGroup.at(5));

    // add question to the proper question tier vector
    questions.at(tier).push_back(question);
}

// returns a random question from the requested tier
Question QuestionManager::GetQuestion(int tier)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + questionCount*10000;
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,questions.at(tier).size()-1);
    questionCount++;

    return questions.at(tier).at(distribution(generator));
}



