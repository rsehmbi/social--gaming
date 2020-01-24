#include "Game.h"
#include "Fighting.h"

using game::Game;
using fighting::Fighting;

Fighting::Fighting(Users player1, Users player2)
  : player1{player1},
    player2{player2} {
      // TODO: get initial health values from JSON file
      player1Health = 100;
      player2Health = 100;
}

Fighting::~Fighting() {
  player1Health = 0;
  player2Health = 0;
  delete player1;
  delete player2;
}

void
Fighting::processAttackMove() {

}

void
Game::mainGameLogic() {

}

std::vector<Users>
Game::getWinner() {

}

void 
Game::requestServer() {

}

bool 
Fighting::hasPlayerLostYet() {
  if (player1Health == 0 || player2Health == 0) {
    return true;
  }
  return false;
}

Users 
Fighting::getLosingPlayer() {
  if (player1Health == 0) {
    return player1;
  }
  return player2;
}

void
Fighting::lowerHealthPoints(User player) {

}