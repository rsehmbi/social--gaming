#ifndef BEAUTY_H
#define BEAUTY_H

#include <string>

namespace beauty{
    
    class Beauty{
        private:
            int roundCount;
            int* votes;
            std::string* answers;
            Users* players;
        public:
            Beauty();
            ~Beauty();

            int getRoundCount();
            int* getVotes();
            std::string* getAnswers();
            Users* getPlayers();

            void setVotes(int* votes);
            void setAnswers(std::string* answers);
            void setPlayers(std::Users* players);

            void updateRoundCount();
            void calculateVotes();
            void calculateWinners();
            
    };
}

#endif 