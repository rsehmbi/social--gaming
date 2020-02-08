#include "ActiveGame.h"
#include "game.h"

using activegame::ActiveGame;
using game::Game;

ActiveGame::ActiveGame(Game game) {
        this->configurations = game.getConfigurations();
        this->rules = game.getRules();
        this->constants = game.getConstants();
        this->state = game.getGameState();
}

game::Configurations
ActiveGame::getConfigs() const {
    return this->configurations;
}

game::GameRules
ActiveGame::getGameRules() const {
    return this->rules;
}

game::Constants
ActiveGame::getConstants() const {
    return this->constants;
}

game::GameState
ActiveGame::getState() {
    return this->state;
}