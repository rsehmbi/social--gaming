#ifndef GAMERULES_H
#define GAMERULES_H

#include "json.hpp"
#include "Rule.h"
#include <vector>

namespace game {

    // This GameRules class is responsible for holding the rules for games
    class GameRules {
    public:
        GameRules();

        void addRule(Rule& rule);
    
        // Used for testing and debugging
        const std::vector<Rule>& getRules();
        std::string toString();
        
    private:
        std::vector<Rule> rules;

    };
}

#endif