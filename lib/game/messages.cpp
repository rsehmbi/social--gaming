#include <iostream>
#include "include/Messages.h"

using game::Messages;
using game::Message;


game::Messages::Messages()
    : messages(){};

const std::vector<Message>
Messages::getMessages(){
    return this->messages;
}

void
Messages::addMessage(const Message& message){
    this->messages.insert(messages.end(), message);
}

std::vector<Message>
Messages::popUpdate(){
    std::vector<Message> temp(this->messages);
    this->messages.empty();
    return temp;
}

        