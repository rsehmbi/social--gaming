#ifndef RULE_H
#define RULE_H

// The Rule class is responsible for holding information relevent
// to executing a rule
class Rule {
public:
    Rule();
    void add();

private:
    // TO DO: Add correct variables types rather than int
    int list;
    int element;
    int until;
    int whileLoop;
    int cases;
    int condition;
    int target;
    int key;
    int from;
    int to;
    int count;
    int value;
    int duration;
    int mode;
    int prompt;
    int choices;
    int result;
    int ascending;
    int score;
    int ruleName;
    int rules;
};


#endif