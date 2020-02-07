
#ifndef SOCIALGAMING_GAMECONFIGURATION_H
#define SOCIALGAMING_GAMECONFIGURATION_H


class GameConfiguration {
private:
    std::string name;
    bool audience;
    int minNoOfPlayers;
    int maxNoOfPlayers;
public:
    std::string getGameName();
    bool hasAudience();
    void setAudienceConfiguration();
    void setMinNoOfPlayers(int minNoOfPlayers);
    void setMaxNoOfPlayers(int maxNoOfPlayers);



};

class GameConstants{
    
};

#endif //SOCIALGAMING_GAMECONFIGURATION_H
