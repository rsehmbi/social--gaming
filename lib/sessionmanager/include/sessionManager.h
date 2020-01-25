// #ifndef SESSIONMANAGER_H
// #define SESSIONMANAGER_H
// #endif

#pragma once //replaces above
#include <deque>
#include <unordered_map>

class sessionManager
{
public:
    sessionManager(); //default constructor

    //add connection as owner of current session
    void addOwner(const Connection& ownerC);

    //add connection to be a player of current session
    void addPlayer(const Connection& playerC);

    //broadcast message to all players in current session
    void broadCast(const std::string& s);

    //send message to a player
    void sendMsg(const unsigned int player, const std::string& s);

    //update incoming session message data from users
    void receiveMsg(std::deque<Message>& messages);


private:
    //a hashed key value pair to map connection id to player number
    extern std::unordered_map<uintptr_t, unsigned int> connectionMap();
    extern std::deque<Message> sessionMessage;
};