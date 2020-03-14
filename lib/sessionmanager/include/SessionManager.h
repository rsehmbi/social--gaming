// #ifndef SESSIONMANAGER_H
// #define SESSIONMANAGER_H
// #endif

#pragma once //replaces above

#include <deque>
#include <unordered_map>
#include <random>
#include <GameSession.h>
#include "Game.h"

using networking::Message;
using networking::Connection;
using game::Game;

// struct to store the game and gameName to easily excess the gameName
// when creating a new game.
struct GameMap {
    int gameId;
    std::string gameName;
    Game game;
};

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
        CommandType checkString(const Message& message);
        
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

        //create and output messages after processMessages has proccessed messages
        const std::deque<Message>& outboundMessages(const std::vector<Connection>& clients);

        //Removes connection info from internal database. Called by onDisconnect in main
        void removeConnection(const ConnectionID& connectionID);

        //function for printer out available games
        std::string getGamesList();

        // set list of available games when the game session is created.
        void setAvailableGames(std::vector <GameMap> availableGames);

    private:

        //a hashed key value pair to map connection id to session id
        std::unordered_map<ConnectionID, SessionID> connectionSessionMap;

        //a map of session id to sessions objects
        std::unordered_map<SessionID, GameSession> sessionMap;

        //chat logs for each session
        //TODO: can remove this since session manager does not need to keep track of session chatlogs
        std::unordered_map<SessionID, std::string> chatLogs;

        //batches of msgs to be sent to each session id
        std::unordered_map<SessionID, MessageBatch> msgsForSession;

        //outbound deque of messages
        std::deque<Message> outgoing;

        //directs message to session
        void sortMessage(const Message& message);

        //create a new session
        void createSession(const ConnectionID& id, const Message& message);

        //join a session
        void joinSession(const ConnectionID& connectionID, const SessionID& sessionID);

        //generate a session id for session creation
        std::string generateID();

        // std::random_device rd;
        //random generator
        std::mt19937 generator;

        CommandChecker commandChecker;

        std::string gamePrompt;

        // List of availableGames to choose from mapped to id and name.
        std::vector<GameMap> availableGames; 

        // Helper function to find the names of available games from available games.
        std::vector<std::string> getAvailableGamesNames();

        // Find game from available games using the game.
        Game& findSelectedGame(std::string gameName);
};

