#ifndef DSL_H
#define DSL_H

#include <string>
#include <map>

// The DSL class is responsible for holding information regarding
// the domain specific language used in JSON files
class DSL {
public:
    // Takes in a configuration file and creates a DSL
    DSL();
    ~DSL();

nlohmann::json inputChoice(nlohmann::json h);

nlohmann::json inputText(nlohmann::json h);

nlohmann::json inputVote(nlohmann::json h);

nlohmann::json message(nlohmann::json h);

nlohmann::json globalMessage(nlohmann::json h);

nlohmann::json scores(nlohmann::json h);

void updateStatus();

private:
    std::map<std::string, std::string> commandMappings;
};

#endif