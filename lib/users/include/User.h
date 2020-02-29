#ifndef SOCIAL_GAMING_USERS_H
#define SOCIAL_GAMING_USERS_H

#include <Server.h>
#include <string>

using networking::ConnectionID;

namespace user {

enum UserType { Player, Owner, Audience };

class User {

    private:
        std::string playerName;
        int playerNum; //Are you player #1,2,3 or 4
        ConnectionID connectionID;   //unique identifier
        enum UserType userType; // Type of the user: { Player, Owner, Audience }

    public:

        //Default Constructor
        User(std::string_view _playerName, int _playerNum, ConnectionID _connectionID, UserType _userType);

        //Getters and Setters to access and change the private variables
        void setPlayerName(std::string_view playerName);

        std::string getPlayerName() const;

        void setPlayerNum(int id);

        int getPlayerNum();

        void setConnectionID(ConnectionID id);

        ConnectionID getConnectionID();

        void setIsPlayer(bool isPlayer);

        bool getIsPlayer();

        void setUserType(UserType _userType);

        UserType getUserType();

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
