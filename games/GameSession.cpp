#include "include/GameSession.h"
#include <iostream>

std::string GameSession::getNameOfGame() {
    if (!this->gameSpecification["configuration"].contains("name")) {
        //If the name of game is not specified in Json Object
        this->gameSpecification["configuration"].emplace("name", "Default Name");
    }
    return this->gameSpecification["configuration"]["name"];
}

int GameSession::getMinNoOfPlayers() {
    // If Configuration don't have the player count, it won't have the min
    if (!this->gameSpecification["configuration"].contains("player count")) {
        this->gameSpecification["configuration"]["player count"].emplace("min", 0);
    }
    return this->gameSpecification["configuration"]["player count"]["min"];
}

int GameSession::getMaxNoOfPlayers() {
    // If Configuration don't have the player count, it won't have the max
    if (!this->gameSpecification["configuration"].contains("player count")) {
        this->gameSpecification["configuration"]["player count"].emplace("max", 0);
    }
    return this->gameSpecification["configuration"]["player count"]["max"];
}

bool GameSession::isAudience() {
    if (!this->gameSpecification["configuration"].contains("audience")) {
        //Set default audience to false or Allow user to update the audience value according to rule specification
        return false;
    }
    return this->gameSpecification["configuration"]["audience"];;
}

std::string GameSession::getConstants(const std::string &nameOfConstant) {
    if (this->gameSpecification["constants"].contains((nameOfConstant))) {
        //Demo Function that will return the constants as strings.
        // Chances are these will change in future.
        return this->gameSpecification["constants"][nameOfConstant].dump();
    }
}

std::string GameSession::getVariables(const std::string &nameOfVariable) {
    //Demo Function that will return the variables as strings.
    // Chances are these will change in future.
    if (this->gameSpecification["variables"].contains(nameOfVariable)) {
        return this->gameSpecification["variables"][nameOfVariable].dump();
    }
}

// How many players are in this one Game Session
int GameSession::getPlayerCount() {
    return this->Players.size();
}

const std::vector <Users> &GameSession::getAudience() const {
    return Audience;
}

const std::vector <Users> &GameSession::getPlayers() const {
    return Players;
}

// Number of people in the audience for a particular Game Session
int GameSession::getAudienceCount() {
    return this->Audience.size();
}

std::list <std::string> GameSession::getPlayerNames() {
    std::list <std::string> namesOfPlayers;
    for (auto iterator: this->Players) {
        namesOfPlayers.push_front(iterator.getPlayerName());
        std::cout << iterator.getPlayerName() << std::endl;
    }
    return namesOfPlayers;
}

json GameSession::getUpdate() {
    //Return the json object for the updates.
    //return json o;
}
