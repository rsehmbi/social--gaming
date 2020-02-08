#include "GameConfiguration.h"
#include "stdlib.h"
#include <string>

GameConfiguration::GameConfiguration(std::string name,bool audience,int minNoOfPlayers,int maxNoOfPlayers):
name(name),audience(audience),minNoOfPlayers(minNoOfPlayers),maxNoOfPlayers(maxNoOfPlayers){
}

void GameConfiguration::setMinNoOfPlayers(int minNoOfPlayers) {
    this->minNoOfPlayers = minNoOfPlayers;
}

void GameConfiguration::setMaxNoOfPlayers(int maxNoOfPlayers) {
    this->maxNoOfPlayers = maxNoOfPlayers;
}
std::string GameConfiguration::getGameName() {
    return this->name;
}
void GameConfiguration::setAudienceConfiguration(bool hasAudience) {
    this->audience = hasAudience;
}

bool GameConfiguration::hasAudience() {
    return this->audience;
}

void GameConfiguration::setGameType(std::string gameType)
{
    this->gameType = gameType;
}

// Game Type to process the input needed from Owner of the game
// For Example : Questions for quiz game
// Numbers of round for a different game
void GameConfiguration::assessGameType(){
  //  if (this->Setup.find("integer").
}

// Consider we are getting input in the form of strings from user
void GameConfiguration::getUserInput(std::string input)
{

}


