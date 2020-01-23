#ifndef BRAWN_H
#define BRAWN_H

namespace brawn {
  
  class Brawn {
    private:
      const Users player1;
      const Users player2;
      int player1Health;
      int player2Health;

    public:
      // Constructs an instance of the Brawn game for two players
      Brawn(Users player1, Users player2);

      // Processes the attacking input and reduces the opponent's health.
      void processAttackInput();

      // Determines if a player has lost yet.
      bool hasPlayerLostYet();

      // Returns the losing player.
      Users getLosingPlayer();
  };
}

#endif