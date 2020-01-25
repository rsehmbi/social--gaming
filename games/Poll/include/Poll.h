#ifndef POLL_H
#define POLL_H

#include <string>
#include "../../../users/include/Users.h"

namespace poll{
    
    class Poll{
        private:
            int roundCount;
            int* votes;
            std::string* answers;
            users::Users* players;
        public:
            Poll();
            ~Poll();

            int getRoundCount();
            int* getVotes();
            std::string* getAnswers();
            users::Users* getPlayers();

            void setVotes(int* votes);
            void setAnswers(std::string* answers);
            void setPlayers(users::Users* players);

            void updateRoundCount();
            void calculateVotes();
            void calculateWinners();
            
    };
}

#endif 