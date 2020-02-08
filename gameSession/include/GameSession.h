#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <string>
#include "Users.h"

class GameSession {

public:
    const std::vector<users::Users> &getAudience() const;

    const std::vector<users::Users> &getPlayers() const;
    //Constructor
    GameSession(json gameSpecification) : gameConfiguration(gameSpecification) {
    };

    std::string getNameOfGame(std::string keyName);

    int getMinNoOfPlayers(std::string keyName);

    int getMaxNoOfPlayers(std::string keyName);

    std::string getConstants(const std::string &nameOfConstant);

    std::string getVariables(const std::string &nameOfVariable);

    bool hasAudience(std::string audiencekey);

    std::vector<std::string> getPlayerNames();

    int getPlayerCount();

    int getAudienceCount();

    void setConstants(const std::string &nameOfConstant);

    // Contains the main logic for the game.
    void mainGameLogic();

    // Returns list of winners for the game.
    // std::vector<users::Users> getWinner();

    // Makes a request to the server.
    // TODO: determine use cases for this method.
    void requestServer();

    // Gets the next user's turn the the game.
    // users::Users nextTurn();

    // Gets a message to display to players of the game.
    void display(std::string);

    json getUpdate();

private:

    json gameConfiguration;

    json constants;
    json variables;

    std::vector<users::Users> Audience;
    std::vector<users::Users> Players;

};

#endif //UNTITLED1_GAMESESSION_H

