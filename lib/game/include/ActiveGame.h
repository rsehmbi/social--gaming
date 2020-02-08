#ifndef ACTIVE_GAME_H
#define ACTIVE_GAME_H

#include "game.h"

using game::game;

namespace activegame {
    
    class ActiveGame {
        public:
            // Constructs an active game by copying the rules, configurations, and constants from a game template.
            // This game template was one of the pre-determined games uplodaded to the server from the server owner
            // and is considered a "blank-slate" game, i.e. this is a game with a un-modified state. 
            ActiveGame(game game);
        private:
            game gameProperty;

            game::configurations configurations;
            game::gameRules rules;
            game::constants constants;
            game::gameState state;
    };
}

#endif