#include "Game.h"
#include "Fighting.h"

using game::Game;
using fighting::Fighting;

Fighting::Fighting() {
  // TODO: change later to be according to number of players in game
  this->maxPlayers = 8;
  players = new users::Users[this->maxPlayers];
  playerHealth = new int[this->maxPlayers];
}

Fighting::~Fighting() {
  this->maxPlayers = 0;
  delete &players;
  delete &playerHealth;
}

void
Fighting::processAttackMove() {

}

void
Game::mainGameLogic() {

}

std::vector<users::Users>
Game::getWinner() {

}

void 
Game::requestServer() {

}

bool 
Fighting::hasPlayerLostYet() {

}

users::Users 
Fighting::getLosingPlayer() {
  
}

void
Fighting::lowerHealthPoints(users::Users player) {

}

void
Fighting::setMaxPlayers(int max) {
  this->maxPlayers = max;
}

int 
Fighting::getMaxPlayers() {
  return this->maxPlayers;
}