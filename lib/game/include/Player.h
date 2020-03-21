#pragma once

#include <variant>
#include <iostream>

namespace game{
using PlayerID = std::variant<int, std::string>;
}
