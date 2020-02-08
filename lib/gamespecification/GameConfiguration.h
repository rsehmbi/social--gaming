
#ifndef SOCIALGAMING_GAMECONFIGURATION_H
#define SOCIALGAMING_GAMECONFIGURATION_H

#include "stdlib.h"
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <cstring>

class GameConfiguration {
public:
    GameConfiguration();
    GameConfiguration(std::string name,bool audience,int minNoOfPlayers,int maxNoOfPlayers);
    std::string getGameName();
    bool hasAudience();
    void setAudienceConfiguration(bool hasAudience);
    void setMinNoOfPlayers(int minNoOfPlayers);
    void setMaxNoOfPlayers(int maxNoOfPlayers);
    void setGameType(std::string Type);
    void getUserInput(std::string Input);
    std::string getGameType();
    void assesGameType();

private:
    std::string name;
    bool audience;
    int minNoOfPlayers;
    int maxNoOfPlayers;
    std::string gameType;
};
#endif //SOCIALGAMING_GAMECONFIGURATION_H

template <class value, class prompt>
struct Setup
{
    std::unordered_map<prompt,value> setupPair;
    prompt promptMessage;
    value inputValue;
    Setup(value &value1, prompt &prompt1) :inputValue(value1), promptMessage(prompt1) {}

    void updateSetup(value &value1, prompt &prompt1)
    {
        this-> inputValue = a;
        this-> promptMessage = b;
        this->setupPair[this->promptMessage] = this->inputValue;
    }

    void updateUserSetup(value &value1, prompt &prompt1)
    {
        this->setupPair[this->promptMessage] = this->inputValue;
        this->setupPair[this->promptMessage] = this->inputValue;
    }
};