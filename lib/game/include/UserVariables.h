#ifndef SOCIAL_GAMING_GAMEUSERS_H
#define SOCIAL_GAMING_GAMEUSERS_H

#include <unordered_map>

#include <Variables.h>

using game::Variables;


namespace game {

class UserVariables {

    private:
        // map from user id to variables for that player.
        std::unordered_map<int, Variables> userVariables;

    public:
        // get the a map of the users Variables available.
        const std::unordered_map<int, Variables>& getUserVariables();

        // add a new user to the list of available users given the player id
        // and the default variables for a player.
        void addNewUser(int _id, const Variables& variables);
    };
}

#endif
