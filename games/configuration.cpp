#include "configuration.h"
#include <string>
#include <iostream>

using configuration:: configuration

configuration::configuration()
{
    this->nameOfGame ="";
    this->audience = false;
    this->playerCount["min"] = 0;
    this->playerCOunt["max"] = 0;
    this->audience = false;
}
configuration::configuration(string nameOfGame, int minNoOfPlayers, int maxNoOfPlayers, bool audience, string setupName,
                             int setupValue) {
    this->nameOfGame = nameOfGame;
    this->audience = audience;
    this->playerCount["min"] = minNoOfPlayers;
    this->playerCOunt["max"] = MaxNoOfPlayers;
    this->setup[setupName] = setupValue;
}
bool configuration::getAudience() {
    return this->audience;
}
int configuration::getGameSetup(string setupName) {
    if (setup.find(setupName) == setup.end())
    {
        // Return the value of the setup name
    }
    else
    {
        return nullptr;
    }

}

int configuration::getMaxPlayerCount() {
    //Return the maximum number of players in a game
}
int configuration::getMinPlayerCount() {
    //Return min number of players for the game
}
string configuration::getNameOfGame() {
    return this->nameOfGame;
}

void configuration::setAudience(bool isAllowed) {
    this->audience =isAllowed;
}
void configuration::setNameOfGame(string name) {
    this->nameOfGame=name;
}
void configuration::setMinPlayerCount(string, int noOfMinPlayers) {
    this->playerCount["min"] = noOfMinPlayers;

}
void configuration::setMaxPlayerCount(string, int noOfMaxPlayers) {
    this->playerCOunt["max"] = noOfMaxPlayers;
}
void configuration::setGameSetup(string nameOfSetup, int value) {
    this->setup[nameOfSetup] = value;
}