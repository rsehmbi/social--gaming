#include "sessionManager.h"

sessionManager::sessionManager() {  // define default constructor
   std::unordered_map<uintptr_t, unsigned int> connectionMap();
   std::deque<Message> sessionMessage();
}

void sessionManager::addOwner(const Connection& ownerC)
{
    
}

void sessionManager::addPlayer(const Connection& playerC)
{

}

void sessionManager::broadCast(const std::string& s)
{

}


void sessionManager::sendMsg(const unsigned int player, const std::string& s)
{

}

void sessionManager::receiveMsg(std::deque<Message>& messages)
{

}
