#ifndef SOCIAL_GAMING_TRIVIA_H
#define SOCIAL_GAMING_TRIVIA_H
#include <string>
class Trivia
{

private:
    int index_questions;
    int index_answers;
    int score;
    int max_questions;
    std::string  *questions;
    std::string *answers;

public:
    Trivia();
    ~Trivia();

    int getindexquestions();
    void setindexquestions(int index);

    int getindexanswers();
    void setindexanswers(int index);

    int getscore();
    void settotalscore(int score);

    int getMax_no_questions();
    void setMax_Questions(int Maxquestions);

};
#endif //SOCIAL_GAMING_TRIVIA_H
