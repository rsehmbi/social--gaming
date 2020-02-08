#ifndef SOCIAL_GAMING_NODES_H
#define SOCIAL_GAMING_NODES_H

#include <string>
#include <vector>
#include <map>

using nlohmann::json;

namespace nodes{
    class Nodes {
    public:
        std::string constantName;
        std::vector<std::map<std::string, std::string>> listOfAttributes;



        void setConstantName(std::string playerName);

        std::string getConstantName() const;
    };
}

#endif