#ifndef GAMES_H
#define GAMES_H

#include <vector>
#include "../../users/include/Users.h"

namespace game {

  class Game {
    public:
      // Contains the main logic for the game.
      void mainGameLogic();

      // Returns list of winners for the game.
      std::vector<users::Users> getWinner();

      // Makes a request to the server.
      // TODO: determine use cases for this method.
      void requestServer();

      // Gets the next user's turn the the game.
      users::Users nextTurn();

      // Gets a message to display to players of the game.
      void display(std::string);
  };
}

#endif