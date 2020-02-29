#include "include/User.h"
#include <string>

using user::User;
using user::UserType;

User::User(std::string_view _username, int _id, ConnectionID _connectionID, UserType _userType)
    : username{_username},
      id{_id},
      connectionID{_connectionID},
      userType{_userType} {
}

//Getters and Setters to access and change the private variables
void User::setName(std::string_view _username){
    this->username = _username;
}

std::string User::getName() const {
    return this->username;
}

void User::setId(int _id){
    this->id = _id;
}

int User::getId(){
    return this->id;
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