#include "Configurations.h"
#include "stdlib.h"
#include <string>

using game::Configurations;

Configurations::Configurations()
{}

Configurations::Configurations(std::string gameName,bool audience,int minNoOfPlayers,int maxNoOfPlayers):
gameName(gameName),audience(audience),minNoOfPlayers(minNoOfPlayers),maxNoOfPlayers(maxNoOfPlayers){
}

bool Configurations::hasAudience() const{
    return this->audience;
}

std::string Configurations::getGameType()
{
    return this->gameType;
}

int Configurations::getMinNoOfPlayers()
{
    return this->minNoOfPlayers;
}

int Configurations::getMaxNoOfPlayers(){
    return this->maxNoOfPlayers;
}

std::string Configurations::getGameName() const
{
    return this->gameName;
}

// Game Type to process the input needed from Owner of the game
// For Example : Questions for quiz game
// Numbers of round for a different game
void Configurations::assessGameType(){
  //  if (this->Setup.find("integer").
}



