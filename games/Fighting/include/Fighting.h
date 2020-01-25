#ifndef FIGHTING_H
#define FIGHTING_H

#include "../../../users/include/Users.h"

namespace fighting {
  
  class Fighting {
    private:
      users::Users *players;
      int *playerHealth;
      int maxPlayers;

    public:
      // Constructs an instance of the Brawn game for two players
      Fighting();

      // Desctructor
      ~Fighting();

      // Processes a certain attack move.
      void processAttackMove();

      // Determines if a player has lost yet.
      bool hasPlayerLostYet();

      // Returns the losing player.
      users::Users getLosingPlayer();

      // Deducts a player's health points.
      void lowerHealthPoints(users::Users player);

      // Sets maximum number of players.
      void setMaxPlayers(int max);

      // Gets the maximum number of players.
      int getMaxPlayers();
  };
}

#endif