#include "include/User.h"
#include <string>

using user::User;
using user::UserType;
using networking::UserIdType;

User::User(std::string_view _username, UserIdType _id, ConnectionID _connectionID, UserType _userType)
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

void User::setId(UserIdType _id){
    this->id = _id;
}

UserIdType User::getId() const {
    return this->id;
}

ConnectionID User::getConnectionID() const {
    return this->connectionID;
}

void User::setUserType(UserType _userType){
    this->userType = _userType;
}

UserType User::getUserType() const {
    return this->userType;
}