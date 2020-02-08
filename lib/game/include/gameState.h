#include <vector>
#include "variables.h"
#include "player.h"
#include "messages.h
#include <nlohmann/json.hpp>

namespace game{
class GameState{
    public:
        GameState(const nlohmann::json& jsonVariables);
        json getUpdate(); //prototype function to return only updated data through json
    private:
        //TODO: need function to check for updated data
        std::vector<game::Player> playerList;
        game::Message messages;
        game::Variables variables;

        game::Variables getVariables(const nlohmann::json& jsonVariables);
}
}