#include "include/GameSession.h"

#include <utility>
#include <iostream>

std::string GameSession::getNameOfGame() {
    if (!this->gameSpecification["configuration"].contains("name"))
    {
        //If the name of game is not specified in Json Object
        this->gameSpecification["configuration"].emplace("name","Default Name");
    }
    return this->gameSpecification["configuration"]["name"];

}

int GameSession::getMinNoOfPlayers() {
    if (!this->gameSpecification["configuration"].contains("player count"))
    {
        this->gameSpecification["configuration"]["player count"].emplace("min",0);
    }
    return this->gameSpecification["configuration"]["player count"]["min"];
}

int GameSession::getMaxNoOfPlayers() {
    if (!this->gameSpecification["configuration"].contains("player count"))
    {
        this->gameSpecification["configuration"]["player count"].emplace("max",0);
    }
    return this->gameSpecification["configuration"]["player count"]["max"];
}

bool GameSession::isAudience() {
    if (!this->gameSpecification["configuration"].contains("audience"))
    {
        //Set default audience to false or Allow user to update the audience value according to rule specification
        return false;
    }
    return this->gameSpecification["configuration"]["audience"];;
}

std::string GameSession::getConstants(const std::string& nameOfConstant) {
    if (this->gameSpecification["constants"].contains((nameOfConstant))) {
        return this->gameSpecification["constants"][nameOfConstant].dump();
    }
}

std::string GameSession::getVariables(const std::string& nameOfVariable) {
    if (this->gameSpecification["variables"].contains(nameOfVariable)) {
        return this->gameSpecification["variables"][nameOfVariable].dump();
    }
}

std::list<std::string> GameSession::getPlayerNames() {
    return this->Players().
}