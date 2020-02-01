#include "include/Users.h"
#include <string>
#include <iostream>

using users::Users;

//Destructor
Users::~Users(){
    this->playerID=0;
    this->isOwner=false;
}

//Getters and Setters to access and change the private variables
void Users::setPlayerName(std::string playerName){
    this->playerName = playerName;
}

std::string Users::getPlayerName() const {
    return this->playerName;
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

//Class Functions to be created after server format is setup
void connectToServer(std::string *passcode);

void sendPlayerInfo(std::string *playerName, int playerID);

void sendResponse(std::string *msg);

void receiveResponse(std::string *msg);