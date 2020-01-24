#ifndef SOCIAL_GAMING_TRIVIA_H
#define SOCIAL_GAMING_TRIVIA_H

#include <string>

namespace trivia {

    class Trivia {
    private:
        int indexQuestions;
        int indexAnswers;
        int currentScore;
        int maxQuestions;
        std::string *questions;
        std::string *answers;

    public:
        //Default Constructor
        Trivia();

        //Destructor
        ~Trivia();

        //Getters and Setters to access and change the private variables
        int getIndexQuestions();

        void setIndexQuestions(int index);

        int getIndexAnswers();

        void setIndexAnswers(int index);

        int getScore();

        void setScore(int score);

        int getMaxNoQuestions();

        void setMaxQuestions(int maxnoquestions);

    };

}
#endif //SOCIAL_GAMING_TRIVIA_H
