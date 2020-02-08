// #ifndef SESSIONMANAGER_H
// #define SESSIONMANAGER_H
// #endif

#pragma once //replaces above

#include <deque>
#include <unordered_map>
#include <Server.h>
#include <random>
#include <iterator>

using networking::Server;
using networking::Connection;
using networking::Message;


//abstract implementation from session class
using SessionMessages = std::deque<Message>;
using SessionID = std::string;
using ConnectionID = uintptr_t;

//----------stub Session struct for testing----//
struct Session
{
    SessionID sessionID;
    void receive(SessionMessages& messages){};
};
//----------stub Session struct for testing----//

//Some info:
//server receives and send deque<Messages>
//Message: {connection, text}

//---------Command Checker and Types------
enum class CommandType {
    NotACommand,
    Create,
    Join,
};

//a wrapper class to map command strings to CommandType to better accomodate future changes 
class CommandChecker{
    public:
        CommandChecker();
        //checks first word of string and returns CommandType. Also updates argument variable accordingly
        CommandType checkString(const std::string& message);
        
        //Returns current value of argument variable
        std::string getArgument();

    private:
        //a hashed key value pair to map connection id to session id
        std::string argument;
        std::unordered_map<std::string, CommandType> commandMap;
};

//-------------------Session Manager Class-------------
//This object manages message sorting for each session
//and passes the messages to specific game sessions.
//It is also responsible for game session creation and join requests.

class SessionManager {

    public:
        SessionManager();

        void processMessages(const std::deque<Message>& incoming);

        const std::deque<Message>& outboundMessages(const std::vector<Connection>& clients);

        // //broadcast message to all players in current session
        void sessionBroadCast(SessionID, std::string text);

        //private message to a connection
        void msgConnection(Message& message);

        //Removes connection info from internal database. Called by onDisconnect in main
        void removeConnection(const ConnectionID& connectionID);


    private:

        //a hashed key value pair to map connection id to session id
        std::unordered_map<ConnectionID, SessionID> connectionSessionMap;

        //a map of session id to sessions objects
        std::unordered_map<SessionID, Session> sessionMap;

        //chat logs for each session
        std::unordered_map<SessionID, std::string> chatLogs;

        //batches of msgs to be sent to each session id
        std::unordered_map<SessionID, SessionMessages> msgsForSession;

        //outbound deque of messages
        std::deque<Message> outgoing;

        //directs message to session
        void sortMessage(const Message& message);

        //create a new session
        void createSession(const ConnectionID& id);

        //join a session
        void joinSession(const ConnectionID& connectionID, const std::string& sessionID);

        //generate a session id for session creation
        std::string generateID();

        // std::random_device rd;
        //random generator
        std::mt19937 generator;

        CommandChecker commandChecker;

};

