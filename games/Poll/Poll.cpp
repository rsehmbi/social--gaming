#include "include/poll.h"

using poll::Poll;

Poll::Poll(){
    this->roundCount = 0;
    this->votes = nullptr;
    this->answers = nullptr;
    this->players = nullptr;
}

Poll::~Poll(){
    this->roundCount = 0;
    delete votes;
    delete answers;
    delete players;
}

int Poll::getRoundCount(){
    return this->roundCount;
}

int* Poll::getVotes(){
    return this->votes;
}

std::string* Poll::getAnswers(){
    return this->answers;
}

users::Users* Poll::getPlayers(){
    return this->players;
}

void Poll::setVotes(int* votes){
    this->votes = votes;
}

void Poll::setAnswers(std::string* answers){
    this->answers = answers;
}


void Poll::setPlayers(users::Users* players){
    this->players = players;
}

void Poll::updateRoundCount(){
    this->roundCount++;
}

void Poll::calculateVotes(){

}

void Poll::calculateWinners(){
    
}
            