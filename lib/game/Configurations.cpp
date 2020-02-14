#include "Configurations.h"
#include "stdlib.h"
#include <string>

using game::Configurations;

Configurations::Configurations()
{}

Configurations::Configurations(std::string name,bool audience,int minNoOfPlayers,int maxNoOfPlayers):
name(name),audience(audience),minNoOfPlayers(minNoOfPlayers),maxNoOfPlayers(maxNoOfPlayers){
}

void Configurations::setMinNoOfPlayers(int minNoOfPlayers) {
    this->minNoOfPlayers = minNoOfPlayers;
}

void Configurations::setMaxNoOfPlayers(int maxNoOfPlayers) {
    this->maxNoOfPlayers = maxNoOfPlayers;
}
std::string Configurations::getGameName() {
    return this->name;
}
void Configurations::setAudienceConfiguration(bool hasAudience) {
    this->audience = hasAudience;
}

bool Configurations::hasAudience() {
    return this->audience;
}

void Configurations::setGameType(std::string gameType)
{
    this->gameType = gameType;
}

// Game Type to process the input needed from Owner of the game
// For Example : Questions for quiz game
// Numbers of round for a different game
void Configurations::assessGameType(){
  //  if (this->Setup.find("integer").
}

// Consider we are getting input in the form of strings from user
void Configurations::getUserInput(std::string input)
{

}


