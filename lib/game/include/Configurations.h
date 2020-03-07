#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "boost/variant.hpp"
#include "stdlib.h"
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include "json.hpp"

 typedef std::string Prompt;
 typedef nlohmann::json QuestionAnswer,MultipleChoice;
 typedef boost::variant< int,std::string, bool,QuestionAnswer,MultipleChoice> Kind;

namespace game{
class Configurations{
public:
    Configurations();
    Configurations(std::string name,bool audience,int minNoOfPlayers,int maxNoOfPlayers);
    std::string getGameName()const;
    bool hasAudience()const;
    void setAudienceConfiguration(bool hasAudience);
    void setMinNoOfPlayers(int &minNoOfPlayers);
    void setMaxNoOfPlayers(int &maxNoOfPlayers);
    void setGameType(std::string &Type);
    void getUserInput(std::string &Input);
    std::string getGameType();
    void assessGameType();
    Prompt prompt;
    std::unordered_map< Prompt, Kind> setup;

private:
    std::string name;
    bool audience;
    int minNoOfPlayers;
    int maxNoOfPlayers;
    std::string gameType;
};

};


#endif

class KindVisitor : public boost::static_visitor<>
{
public:
//These are just examples, the actions only need to be able to touch
// internal variables.
void operator()(int &t){
   //
}

void operator()(std::string &t){
   //
}

void operator()(bool &t){
   //
}

void operator()(QuestionAnswer &t){
   //
}

};
