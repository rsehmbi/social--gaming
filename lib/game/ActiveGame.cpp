#include "ActiveGame.h"
#include "game.h"

using activegame::ActiveGame;
using game::game;

ActiveGame::ActiveGame(game game)
    :gameProperty{game} {
        this->configurations = game.getConfigurations();
        this->rules = game.getRules();
        this->constants = game.getConstants();
        this->state = game.getGameState();
}