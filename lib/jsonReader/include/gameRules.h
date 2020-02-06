#ifndef GAMERULES_H
#define GAMERULES_H

#include "../interpreter/include/json.hpp"
#include "include/rule.h"

// This GameRules class is responsible for holding the rules for games
class GameRules {
public:
    GameRules();
    ~GameRules();

    // Gets game rules from JSON file
    void getGameRules(nlohmann::json jsonRules);
    // Used for testing only
    void printRules();
    
private:
    std::vector<Rule> rules;

};

#endif