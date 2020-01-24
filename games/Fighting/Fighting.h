#ifndef FIGHTING_H
#define FIGHTING_H

namespace fighting {
  
  class Fighting {
    private:
      const Users player1;
      const Users player2;
      int player1Health;
      int player2Health;

    public:
      // Constructs an instance of the Brawn game for two players
      Fighting(Users player1, Users player2);

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
  };
}

#endif