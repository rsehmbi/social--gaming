#include <vector>
#include "element.h"

namespace game{
class Variables{
    public:
        Variables(const std::vector<Element>& variables);
    private:
        std::vector<Element> variables;
};
}