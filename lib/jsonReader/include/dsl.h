#ifndef DSL_H
#define DSL_H

#include <string>
#include <map>
#include "json.hpp"

using nlohmann::json;

// The DSL class is responsible for holding information regarding
// the domain specific language used in JSON files
namespace dsl{

class DSL {
public:
    // Takes in a configuration file and creates a DSL
    DSL();

nlohmann::json add(json& rule);

nlohmann::json inputChoice(const nlohmann::json& h);

nlohmann::json inputText(const nlohmann::json& h);

nlohmann::json inputVote(const nlohmann::json& h);

nlohmann::json message(const nlohmann::json& h);

nlohmann::json globalMessage(const nlohmann::json& h);

nlohmann::json scores(const nlohmann::json& h);

nlohmann::json timer(const nlohmann::json& h);

void updateStatus();

private:
    std::map<std::string, std::string> commandMappings;
};    
}
#endif