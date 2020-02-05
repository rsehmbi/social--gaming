#include "GameSession.h"
#include <iostream>

// Based on the comments this key value pair can be exacted by only using one function,
// We can change the functions for game session here as the requirement changes.
std::string GameSession::getNameOfGame(std::string namekey) {
    if (this->gameConfiguration.contains(namekey)) {
        //If the name of game is not specified in Json Object
        return this->gameConfiguration[namekey];
    }
    else{
        //Use default data or get data from users
    }
}

int GameSession::getMinNoOfPlayers(std:: string minPlayerKey) {
    // If Configuration don't have the player count, it won't have the min
    if (!this->gameConfiguration.contains(minPlayerKey)) {
        //Handles if the minimum number of players key is not in Json Configuration Object
        return this->gameConfiguration[minPlayerKey];
    }else{
        //Use default data or get data from users
    }
}

int GameSession::getMaxNoOfPlayers(std:: string maxPlayerKey) {
    // If Configuration don't have the player count, it won't have the max
    if (this->gameConfiguration.contains(maxPlayerKey)) {
       return this->gameConfiguration[maxPlayerKey];
    }
     else {
        //Use default data or get data from users
    }
}

bool GameSession::hasAudience(std::string audiencekey) {
    if (this->gameConfiguration.contains(audiencekey)) {
        //Set default audience to false or Allow user to update the audience value according to rule specification
        return this->gameConfiguration[audiencekey];
    }
    else {
        //Use default data or get data from users
    }

}

std::string GameSession::getConstants(const std::string &nameOfConstant) {
    if (this->gameConfiguration.contains((nameOfConstant))) {
        //Demo Function that will return the constants as strings.
        // Chances are these will change in future.
        return this->gameConfiguration[nameOfConstant].dump();
    }
    else {
        //Use default data or get data from users
    }
}

std::string GameSession::getVariables(const std::string &nameOfVariable) {
    //Demo Function that will return the variables as strings.
    // Chances are these will change in future.
    if (this->gameConfiguration.contains(nameOfVariable)) {
        return this->gameConfiguration[nameOfVariable].dump();
    }
    else {
        //Use default data or get data from users
    }
}

// How many players are in this one Game Session
int GameSession::getPlayerCount() {
    return this->Players.size();
}

const std::vector<users::Users> &GameSession::getAudience() const {
    return Audience;
}

const std::vector<users::Users> &GameSession::getPlayers() const {
    return Players;
}

// Number of people in the audience for a particular Game Session
int GameSession::getAudienceCount() {
    return this->Audience.size();
}

std::vector<std::string> GameSession::getPlayerNames() {
    std::vector<std::string> namesOfPlayers;
    for (auto iterator: this->Players) {
        namesOfPlayers.push_back(iterator.getPlayerName());
        std::cout << iterator.getPlayerName() << std::endl;
    }
    return namesOfPlayers;
}

json GameSession::getUpdate() {
    //Return the json object for the updates.
    //return json o;
}


GameSession::GameSession(std::string_view specifications, std::string_view configurations){
    jsonReader::jsonReader jReader = jsonReader::jsonReader();
    json jsonGameObject = jReader.gameJsonFromJson(specifications, configurations);
    if (jsonGameObject == nullptr){
        game = createGame(jsonGameObject);
    } else {
        LOG(ERROR) << "Could not start game session. Error reading the json";
    }
}

Game::game GameSession::createGame(const json& jsonGameObject){

}