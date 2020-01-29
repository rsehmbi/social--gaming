#ifndef SOCIAL_GAMING_CONFIGURATION_H
#define SOCIAL_GAMING_CONFIGURATION_H
#include <unordered_map>
#include <string>
#include <iostream>

namespace configuration
{
    class configuration{
    private:
        string nameOfGame;
        unordered_map <string, int> playerCount;
        bool audience;
        unordered_map <string, int> setup;

    public:
        // constructors
        configuration();
        configuration(string nameOfGame,int minNoOfPlayers, int maxNoOfPlayers, bool audience, string setupName, int setupValue );

        // Destructors
        ~configuration();

        // Getters to get the values of the private fiels
        string getNameOfGame();
        int getMinPlayerCount();
        int getMaxPlayerCount();
        bool getAudience();
        int getGameSetup();

        // Helps in setting the name of the Game
        void setNameOfGame(string name);

        // Helps in setting the minimum number of players
        void setMinPlayerCount(string = "min", int noOfMinPlayers);

        //Helps in setting the maximum number of players
        void setMaxPlayerCount(string = "max", int noOfMaxPlayers);

        //Helps to know if audience is allowed in game or not
        void setAudience(bool);

        // Game Setup tells us info like number of rounds or number of questions in a game
        void setGameSetup(string nameOfSetup, int value);
    };
}

#endif //SOCIAL_GAMING_CONFIGURATION_H