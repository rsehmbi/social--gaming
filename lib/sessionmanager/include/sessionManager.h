// #ifndef SESSIONMANAGER_H
// #define SESSIONMANAGER_H
// #endif

#pragma once //replaces above

#include <deque>
#include <unordered_map>
#include <Server.h>
#include <random>

using networking::Server;
using networking::Connection;
using networking::Message;

//----------stub Session struct for testing----//
struct Session
{
    std::string sessionID;
};

//Some info:
//server receives and send deque<Messages>
//Message: {connection, text}

//This object manages message sorting for each session
//and passes the messages to specific game sessions

class SessionManager
{
public:
    SessionManager(); //constructor

    ~SessionManager(); //destructor

    void processMessages(const std::deque<Message>& incoming);

    const std::deque<Message>& outboundMessages(const std::vector<Connection>& clients);

    //add connection as owner of current session
    // void addOwner(const Connection& ownerC);

    // //add connection to be a player of current session
    // void addPlayer(const Connection& playerC);

    // //broadcast message to all players in current session
    // void broadCast(const std::string& s);

    // //send message to a player
    // void sendMsg(const unsigned int player, const std::string& s);

    // //update incoming session message data from users
    // void receiveMsg(std::deque<Message>& messages);


private:
    //a hashed key value pair to map connection id to session id
    //use owner id for the session id since it is unique to begin with
    std::unordered_map<uintptr_t, std::string> connectionMap;

    //a hashed key value pair to map session id to sessions objects
    std::unordered_map<std::string, Session> sessionMap;

    //chat logs for each session
    std::unordered_map<std::string, std::string> sessionLogs;

    //outbound deque of messages
    std::deque<Message> outgoing;

    //create a new session
    void createSession(const uintptr_t& id);

    //join a session
    void joinSession(const uintptr_t& connectionID, const std::string& sessionID);

    //generate a session id for session creation
    std::string generateID();

    //initialize a random generator
    std::random_device rand_dev;//seed for mt19937
    std::mt19937 generator;
};