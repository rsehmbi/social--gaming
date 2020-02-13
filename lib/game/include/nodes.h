#ifndef SOCIAL_GAMING_NODES_H
#define SOCIAL_GAMING_NODES_H

#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using nlohmann::json;

typedef std::map<std::string, std::string> mapStringToString;

namespace nodes{
    class Nodes {
    public:
        std::string constantName;
        std::vector<mapStringToString> listOfAttributes;



        void setConstantName(std::string playerName);

        std::string getConstantName() const;
    };
}

#endif