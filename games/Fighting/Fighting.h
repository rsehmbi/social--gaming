#ifndef FIGHTING_H
#define FIGHTING_H

namespace fighting {
  
  class Fighting {
    private:
      Users *players;
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
      Users getLosingPlayer();

      // Deducts a player's health points.
      void lowerHealthPoints(User player);

      // Sets maximum number of players.
      void setMaxPlayers(int max);

      // Gets the maximum number of players.
      int getMaxPlayers();
  };
}

#endif