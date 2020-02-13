#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include "include/Element.h"

namespace game{
class Variables{
    public:
        Variables();
        Variables(const std::vector<game::Element>& variables);

        const std::vector<Element> getVariables();
    private:
        std::vector<Element> variables;
};
}

#endif