#ifndef SOCIAL_GAMING_USERS_H
#define SOCIAL_GAMING_USERS_H

#include <string>

namespace users {
    class Users {
    private:
        std::string playerName;
        int playerNum; //Are you player #1,2,3 or 4
        int playerID;   //unique identifier
        bool isOwner; //if player is the Owner of game
        int NumOfWins;


    public:
        //Default Constructor
        Users(std::string playername, int playerNum, int PlayerID, bool isOwner, int NumOfWins) : playerName(
                playername), playerNum(playerNum), playerID(PlayerID), isOwner(isOwner), NumOfWins(NumOfWins) {};

        //Destructor
        ~Users();

        //Getters and Setters to access and change the private variables
        void setPlayerName(std::string playerName);

        std::string getPlayerName() const;

        void setPlayerNum(int id);

        int getPlayerNum();

        void setPlayerID(int id);

        int getPlayerID();

        void setIsOwner(bool owner);

        bool getIsOwner();

        //Class Functions
        void connectToServer(std::string *passcode);

        void sendPlayerInfo(std::string *playerName, int playerID);

        void sendResponse(std::string *msg);

        void receiveResponse(std::string *msg);

    };
}

#endif