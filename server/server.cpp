#include "server.h"

//data structures for storing information
std::unorder_set<userID> users();
std::unorder_set<roomID> rooms();

Server::Server() {  // define default constructor

   //implementation
}

userID Server::registerUser()
{
    
}

void Server::deleteUser(userID uID)
{

}

roomID Server::createRoom(user ID)
{
    /*
    Possible implementation:
    Receives request from user ID and creates a session/room. 
    Return the session/room number to user to share with others
    */
}


void Server::joinRoom(roomID ID, user ID)
{
    /*
    Possible implementation:
    use sessionID to join a room. Need to workout concept of room communication
    */
}

void Server::deleteRoom(roomID rID)
{

}

    //send msg to user
void Server::sendUser(userID uID)
{

}

    //receive msg from user
void Server::fromUser(userID uID)
{

}
