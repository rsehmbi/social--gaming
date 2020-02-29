#include "include/User.h"
#include <string>

using user::User;
using user::UserType;

User::User(std::string_view _playerName, int _playerNum, ConnectionID _connectionID, UserType _userType)
    : playerName{_playerName},
      playerNum{_playerNum},
      connectionID{_connectionID},
      userType{_userType} {

}

//Getters and Setters to access and change the private variables
void User::setPlayerName(std::string_view playerName){
    this->playerName = playerName;
}

std::string User::getPlayerName() const {
    return this->playerName;
}

void User::setPlayerNum(int num){
    this->playerNum = num;
}

int User::getPlayerNum(){
    return this->playerNum;
}

void User::setConnectionID(ConnectionID connectionID){
    this->connectionID = connectionID;
}

ConnectionID User::getConnectionID(){
    return this->connectionID;
}

void User::setUserType(UserType _userType){
    this->userType = _userType;
}

UserType User::getUserType(){
    return this->userType;
}

//Class Functions to be created after server format is setup
void connectToServer(std::string *passcode);

void sendPlayerInfo(std::string *playerName, int playerID);

void sendResponse(std::string *msg);

void receiveResponse(std::string *msg);
