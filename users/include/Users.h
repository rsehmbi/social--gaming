#ifndef SOCIAL_GAMING_USERS_H
#define SOCIAL_GAMING_USERS_H

namespace users {
    class Users {
    private:
        std::string playerName;
        int playerNum; //Are you player #1,2,3 or 4
        int playerID;   //unique identifier
        bool isPlayer; // True if User is an player of a game, false if they are an audience member

    public:
        //Default Constructor
        Users(std::string& playername, int playerNum, int PlayerID, bool isPlayer);

        //Getters and Setters to access and change the private variables
        void setPlayerName(std::string& playerName);

        std::string getPlayerName() const;

        void setPlayerNum(int id);

        int getPlayerNum();

        void setPlayerID(int id);

        int getPlayerID();

        void setIsPlayer(bool isPlayer);

        bool getIsPlayer();

        //Class Functions
        void connectToServer(std::string *passcode);

        void sendPlayerInfo(std::string *playerName, int playerID);

        void sendResponse(std::string *msg);

        void receiveResponse(std::string *msg);

        int getNumOfWins();

        void setNumOfWins();

    };
}

#endif
