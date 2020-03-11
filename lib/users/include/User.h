#ifndef SOCIAL_GAMING_USERS_H
#define SOCIAL_GAMING_USERS_H

#include <Server.h>
#include <string>

using networking::ConnectionID;

namespace user {

enum UserType { Player, Owner, Audience };

class User {

    private:
        std::string username;
        int id; // Unique id of the player.
        ConnectionID connectionID;   //unique identifier
        enum UserType userType; // Type of the user: { Player, Owner, Audience }

    public:

        //Default Constructor
        User(std::string_view _username, int _id, ConnectionID _connectionID, UserType _userType);

        //Getters and Setters to access and change the private variables
        void setName(std::string_view _username);

        std::string getName() const;

        void setId(int id);

        int getId() const;

        ConnectionID getConnectionID() const;

        void setUserType(UserType _userType);

        UserType getUserType() const;

        //Class Functions
        int getNumOfWins();

        void setNumOfWins();
    };
}

#endif
