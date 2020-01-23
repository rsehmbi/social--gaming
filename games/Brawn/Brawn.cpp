#include "Game.h"
#include "Brawn.h"

using game::Game;
using brawn::Brawn;

Brawn::Brawn(Users player1, Users player2)
  : player1{player1},
    player2{player2} {
      player1Health = 100;
      player2Health = 100;
}

void
Brawn::processAttackInput() {
  
}

void
Game::mainGameLogic() {

}

std::vector<Users>
Game::getWinners() {

}

void 
Game::requestServer() {

}

bool 
Brawn::hasPlayerLostYet() {
  if (player1Health == 0 || player2Health == 0) {
    return true;
  }
  return false;
}

Users 
Brawn::getLosingPlayer() {
  if (player1Health == 0) {
    return player1;
  }
  return player2;
}