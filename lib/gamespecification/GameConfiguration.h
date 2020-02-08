
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
    //std::unordered_map<boost::variant<int,bool,std::string>>,std::string> Setup;
    void AssesGameType();

private:
    std::string name;
    bool audience;
    int minNoOfPlayers;
    int maxNoOfPlayers;
    std::string gameType;
};
#endif //SOCIALGAMING_GAMECONFIGURATION_H

template <class kind, class prompt>
struct setup
{
    std::unordered_map<kind,prompt> setupPair;
    kind x;
    prompt y;

    setup(kind a, prompt b) :x(a), y(b) {}
    void updateSetup(kind a, prompt b)
    {
        this-> x = a;
        this-> y = b;
        this->setupPair[x] = y;
        std::cout<< this->setupPair[a] << std::endl;
        std::cout<<a<<std::endl;
        std::cout<<b<<std::endl;
    }

    void updateUserSetup(kind a, prompt b)
    {
        std::cin >> b;
        this->setupPair[this->x] = b;
        std::cout << b <<std::endl;
        setupPair[a] = b ;
    }
};