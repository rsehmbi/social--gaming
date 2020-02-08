#ifndef GAMERULES_H
#define GAMERULES_H

#include "../interpreter/include/json.hpp"
#include "include/Rule.h"
#include <vector>

namespace game {
    
    // This GameRules class is responsible for holding the rules for games
    class GameRules {
    public:
        GameRules();

        void addRule(Rule& rule);
        
        // Gets game rules from JSON file
        // Will be moved to a separate convertor class
        void getRulesByConverting(nlohmann::json jsonRules);
        
        // Used for testing only
        const std::vector<Rule>& getRules();
        
    private:
        std::vector<Rule> rules;

    };
}

#endif