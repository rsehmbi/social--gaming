#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "boost/variant.hpp"
#include "stdlib.h"
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include "json.hpp"

using Prompt =  std::string;
using MultipleChoice = nlohmann::json; 
using QuestionAnswer = nlohmann::json;
using Kind = boost::variant< int,std::string, bool,QuestionAnswer,MultipleChoice> ;

namespace game{
class Configurations{
public:
   Configurations();
   Configurations(std::string name,bool audience,int minNoOfPlayers,int maxNoOfPlayers);

   std::string getGameName()const;
   int getMinNoOfPlayers();
   int getMaxNoOfPlayers();
   bool hasAudience()const;

   std::string getGameType();
   void assessGameType();
   Prompt prompt;
   std::unordered_map< Prompt, Kind> setup;

private:
   std::string gameName;
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
