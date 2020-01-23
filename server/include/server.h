/*
Server header file. Purpose of server object is to act as a message
relay between game object and users to provide a plaform where 
multiple users can interact with a game
*/

// #ifndef SERVER_H
// #define SERVER_H
// #endif

#pragma once //replaces above
#include <unordered_set>

class Server
{
public:
    Server(); //default constructor

    //User requests ID from server
    userID registerUser();

    //delete user
    void deleteUser(userID uID);

    //Create a new room
    roomID Server::createSession(userID uID);

    //Join a room
    void joinRoom(roomID rID, userID uID);

    //delete a room
    void deleteRoom(roomID rID);

    //send msg to user
    void sendUser(userID uID);

    //receive msg from user
    void fromUser(userID uID);


private:
    //a hash set for user id records
    extern std::unorder_set<userID> users();
    
    //a has set for room id records
    extern std::unorder_set<roomID> rooms();
};