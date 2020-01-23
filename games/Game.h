#ifndef GAMES_H
#define GAMES_H

#include <vector>

namespace game {

  class Game {
    public:
      // Contains the main logic for the game.
      void mainGameLogic();

      // Returns list of winners for the game.
      std::vector<Users> getWinners();

      // Makes a request to the server.
      // TODO: determine use cases for this method.
      void requestServer();
  };
}

#endif