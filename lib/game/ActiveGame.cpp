#include "ActiveGame.h"
#include "game.h"

using activegame::ActiveGame;
using game::Game;

ActiveGame::ActiveGame(Game game)
    :gameProperty{game} {
        this->configurations = game.getConfigurations();
        this->rules = game.getRules();
        this->constants = game.getConstants();
        this->state = game.getGameState();
}