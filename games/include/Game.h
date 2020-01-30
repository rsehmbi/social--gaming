#ifndef GAMES_H
#define GAMES_H

#include <vector>
#include <string>
#include <map>
#include "../../users/include/Users.h"
#include "configuration.h"

namespace game {

  class Game {
      configuration gameConfiguration;

      map <string, std:: map<string, string>>constants;
      std::map<std::string,std:: string> constantAttributes;

      std::map <std::string, list <std::string>> variables;
      list <std::string> variablesAttributes;

      std::map< string, list<int>>perPlayer;
      list <int> perPlayerAttributes;

      std::map< string, list<int>>perAudience;
      list <int> perAudienceAttributes;

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