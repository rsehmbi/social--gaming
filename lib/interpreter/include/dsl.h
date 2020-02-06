#ifndef DSL_H
#define DSL_H

#include <string>
#include <map>
#include "json.hpp"

using nlohmann::json;

// The DSL class is responsible for holding information regarding
// the domain specific language used in JSON files
class DSL {
public:
    // Takes in a configuration file and creates a DSL
    DSL();
    // Adds one list to another
    static json extend(json rules);
    // Reverses a list
    static json reverse(json rules);

private:
    std::map<std::string, std::string> commandMappings;
};

#endif