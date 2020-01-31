#include "include/Users.h"
#include <string>
#include <iostream>

using users::Users;

//Constructor
Users::Users() {
    playerName= new std::string;
    this->playerID= 0;
    this->isOwner= false;
    this->wins = 0;
};

//Destructor
Users::~Users(){
    delete[]playerName;
    this->playerID=0;
    this->isOwner=false;
    this->wins = 0;
}

//Getters and Setters to access and change the private variables
void Users::setPlayerName(std::string *playerName){
    this->playerName= playerName;
}

std::string Users::getPlayerName(){
    return *this->playerName;
}

void Users::setPlayerNum(int num){
    this->playerNum=num;
}

int Users::getPlayerNum(){
    return this->playerNum;
}

void Users::setPlayerID(int id){
    this->playerID=id;
}

int Users::getPlayerID(){
    return this->playerID;
}

void Users::setIsOwner(bool owner){
    this->isOwner=owner;
}

bool Users::getIsOwner(){
    return this->isOwner;
}

int Users::getWins() {
    return this->wins;
}

void Users::setWins() {
    this->wins = ++this->wins;
}

//Class Functions to be created after server format is setup
void connectToServer(std::string *passcode);

void sendPlayerInfo(std::string *playerName, int playerID);

void sendResponse(std::string *msg);

void receiveResponse(std::string *msg);