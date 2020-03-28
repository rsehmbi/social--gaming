#include <UserVariables.h>

using game::UserVariables;

const std::unordered_map<int, Variables>& 
UserVariables::getUserVariables() {
    return userVariables;
}

void 
UserVariables::addNewUser(int _id, const Variables& variables){
    userVariables.emplace(std::make_pair(_id, variables));
}