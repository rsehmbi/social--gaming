#include "include/Users.h"
#include <string>
#include <iostream>

using users::Users;

Users::Users(std::string& playername, int& playerNum, int& playerID, bool& isPlayer)
    : playerName{playerName},
      playerNum{playerNum},
      playerID{playerID},
      isPlayer{isPlayer} {

}

//Getters and Setters to access and change the private variables
void Users::setPlayerName(std::string& playerName){
    this->playerName = playerName;
}

std::string Users::getPlayerName() const {
    return this->playerName;
}

void Users::setPlayerNum(int& num){
    this->playerNum=num;
}

int Users::getPlayerNum(){
    return this->playerNum;
}

void Users::setPlayerID(int& id){
    this->playerID=id;
}

int Users::getPlayerID(){
    return this->playerID;
}

void Users::setIsPlayer(bool& player){
    this->isPlayer=player;
}

bool Users::getIsPlayer(){
    return this->isPlayer;
}

//Class Functions to be created after server format is setup
void connectToServer(std::string *passcode);

void sendPlayerInfo(std::string *playerName, int playerID);

void sendResponse(std::string *msg);

void receiveResponse(std::string *msg);
