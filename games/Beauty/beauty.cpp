#include "include/beauty.h"

using beauty::Beauty;

Beauty::Beauty(){
    this->roundCount = 0;
    this->votes = nullptr;
    this->answers = nullptr;
    this->players = nullptr;
}

Beauty::~Beauty(){
    this->roundCount = 0;
    delete votes;
    delete answers;
    delete players;
}

int Beauty::getRoundCount(){
    return this->roundCount;
}

int* Beauty::getVotes(){
    return this->votes;
}

std::string* Beauty::getAnswers(){
    return this->answers;
}

Users* Beauty::getPlayers(){
    return this->players;
}

void Beauty::setVotes(int* votes){
    this->votes = votes;
}

void Beauty::setAnswers(std::string* answers){
    this->answers = answers;
}


void Beauty::setPlayers(std::Users* players){
    this->players = players;
}

void Beauty::updateRoundCount(){
    this->roundCount++;
}

void Beauty::calculateVotes(){

}

void Beauty::calculateWinners(){
    
}
            