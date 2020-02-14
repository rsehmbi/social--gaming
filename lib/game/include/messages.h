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
        const std::vector<Message> getMessages();
        void addMessage(const Message& message);
        std::vector<Message> getUpdate(); // only return updated messages
    private:
        std::vector<Message> messages;
};
}