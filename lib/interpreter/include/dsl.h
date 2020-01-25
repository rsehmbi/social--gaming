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

private:
    std::map<std::string, std::string> commandMappings;
};

#endif