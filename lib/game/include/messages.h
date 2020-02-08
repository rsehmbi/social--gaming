#include<iostream>
#include<vector>

namespace game{

struct Message{
    std::string from;
    std::string to;
    std::string content;
};

class Messages{
    public:
        Messages();
        std::vector<std::string> getMessages();
        void addMessage(Message message);
        std::vector<Message> getUpdate(); // only return updated messages
    private:
        std::vector<Message> messages;
};
}