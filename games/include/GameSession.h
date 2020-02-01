#ifndef UNTITLED1_GAMESESSION_H
#define UNTITLED1_GAMESESSION_H

#include <list>
#include <utility>
#include "json.hpp"
#include "users/include/Users.h"

using json = nlohmann::json;

class GameSession {
private:

    json gameSpecification;

    json constants;
    json variables;

    std::vector <Users> Audience;
    std::vector <Users> Players;

public:
    //Constructor
    GameSession(json gameSpecification) : gameSpecification(gameSpecification) {
    };

    std::string getNameOfGame();

    int getMinNoOfPlayers();

    int getMaxNoOfPlayers();

    std::string getConstants(const std::string &nameOfConstant);

    std::string getVariables(const std::string &nameOfVariable);

    bool isAudience();

    std::list <std::string> getPlayerNames();

    int getPlayerCount();

    int getAudienceCount();

    void setConstants(const std::string &nameOfConstant);

    const std::vector <Users> &getAudience() const;

    const std::vector <Users> &getPlayers() const;

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

};

#endif //UNTITLED1_GAMESESSION_H

