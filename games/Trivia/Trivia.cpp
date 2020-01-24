#include "include/Trivia.h"
#include <string>
#include <iostream>

Trivia::Trivia()
{
    this->index_questions = 0;
    this->index_answers = 0;
    this->max_questions = 10;
    questions = new std::string [this->max_questions];
    answers = new std::string [this->max_questions];
}

Trivia::~Trivia()
{
    this->index_questions = 0;
    this->index_answers = 0;
    this->score = 0;
    int max_questions = 0;
    delete []questions;
    delete []answers;
}

int Trivia :: getindexquestions()
{
    return this->index_questions;
}

void Trivia :: setindexquestions(int index)
{
    this->index_questions = index;
}

int Trivia :: getindexanswers()
{
    return this->index_answers;
}

void Trivia:: setindexanswers(int index)
{
    this->index_answers = index;
}

int Trivia :: getscore()
{
    return this->score;
}

void Trivia::settotalscore(int score)
{
    this->score =  score;
}

int Trivia::getMax_no_questions() {
    return this->max_questions;
}
void Trivia::setMax_Questions(int Maxquestions) {
    this->max_questions = Maxquestions;
}

