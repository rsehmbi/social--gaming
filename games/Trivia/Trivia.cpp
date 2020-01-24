#include "include/Trivia.h"
#include <string>
#include <iostream>

using trivia::Trivia;

//Default Constructor
Trivia::Trivia() {
    this->indexQuestions = 0;
    this->indexAnswers = 0;
    this->maxQuestions = 10;
    questions = new std::string[this->maxQuestions];
    answers = new std::string[this->maxQuestions];
}

//Destructor
Trivia::~Trivia() {
    this->indexAnswers = 0;
    this->indexQuestions = 0;
    this->currentScore = 0;
    this->maxQuestions = 0;
    delete[]questions;
    delete[]answers;
}

//Getter and Setters
int Trivia::getIndexQuestions()
{
    return this->indexQuestions;
}

void Trivia::setIndexQuestions(int index)
{
    this->indexQuestions = index;
}

int Trivia::getIndexAnswers()
{
    return this->indexAnswers;
}

void Trivia::setIndexAnswers(int index)
{
    this->indexAnswers = index;
}

int Trivia::getScore()
{
    return this->currentScore;
}

void Trivia::setScore(int score)
{
    this->currentScore = score;
}

int Trivia::getMaxNoQuestions()
{
    return this->maxQuestions;
}

void Trivia::setMaxQuestions(int maxnoquestions)
{
    this->maxQuestions = maxnoquestions;
}

