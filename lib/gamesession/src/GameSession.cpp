#include <GameSession.h>

#include <ctime>
#include <glog/logging.h>
#include <sstream>
#include <iostream>


static const std::string MSG_NO_ROOM_FOR_PLAYER = "No room for a new player";

//Initialized by the session manager, session manager will pass 
//in game type argument containing game information
GameSession::GameSession(SessionID id, ConnectionID ownerConnectionId, const GameRules& _rules, 
    const GameState& _gameState, Configurations _configurations)
    :   rules(_rules),
        configurations(_configurations),
        initialState(_gameState),
        sessionID{id},
        owner{User {"", static_cast<UserIdType>(1), ownerConnectionId, UserType::Owner} }
{   
    sessionUsers.push_back(owner);
    gameStarted = false;
    LOG(INFO) << "Session created with id: " << sessionID;
}

MessageBatch
GameSession::processGameTurn(const MessageBatch& inMsgs, std::shared_ptr<Interpreter> interpreter){
    MessageBatch msgBuffer;
    
     /* 
        Game starts only when the owner of the game starts the game.
        This set of statements checks at every tick if the game has started
        and process the rules only if the game has started.
    */
    if (gameStarted && checkTimeOuts()) { 
        interpreter->setCurrentGameSession(this, &currentState, &rules);

        //-----------perform game turn-------
        for(auto& msg : inMsgs){
            std::ostringstream out;

            // Find the user sending the message.
            auto it = std::find_if(sessionUsers.begin(), sessionUsers.end(), 
                [&msg] (User& user) { return user.getConnectionID() == msg.connection.id; }
            );

            // Save the incoming message from the user in the map to be used by the interpreter.
            if (it != sessionUsers.end()){
                User user = *it;
                MessageText messageText = {msg.text};
                currentState.messageMap[user.getId()] = messageText;
            }

            //FOR TESTING: send msg back to each player
            // out << msg.connection.id << "> " << msg.text << "\n";
            // msgBuffer.push_back({{msg.connection.id}, out.str()});
        }

        //-----------end of perform game turn-------
    }

    // send all the incoming messages out in the current tick.
    std::transform(std::make_move_iterator(outMsgs.begin()), 
        std::make_move_iterator(outMsgs.end()),
        std::back_inserter(msgBuffer), 
        [](auto&& msg) { return std::move(msg); }
    );
    outMsgs.clear();

    return msgBuffer;
}

void 
GameSession::sessionBroadCast(const std::string& text){
    for (const User& user : sessionUsers){
        msgConnection(user.getConnectionID(), text);
    }
}

void
GameSession::msgUsersOfType(UserType userType, const std::string& text){
    if (userType == UserType::Owner){
        msgConnection(owner.getConnectionID(), text);
    } else {
        for (const User& user : sessionUsers){
            if (user.getUserType() == userType)
                msgConnection(user.getConnectionID(), text);
        }
    }
}

void 
GameSession::msgUser(UserIdType id, const std::string& text){
    auto it = std::find_if(sessionUsers.begin(), sessionUsers.end(), 
        [id] (User& user) { return user.getId() == id; }
    );

    if (it != sessionUsers.end()){
        User user = *it;
        msgConnection(user.getConnectionID(), text);
    }
}

void 
GameSession::msgConnection(const ConnectionID& target, const std::string& msg){
    LOG(INFO) << "Sending message to connection: " << target;
    outMsgs.push_back({{target}, msg});
}

void 
GameSession::disconnect(const ConnectionID& cid){
    sessionUsers.erase(std::remove_if(sessionUsers.begin(), sessionUsers.end(), 
        [&cid] (User& user) {return user.getConnectionID() == cid;})
    );
}

void 
GameSession::connect(const ConnectionID& cid, const NewUserType newUserType, const std::string_view& userName){
    if (gameStarted){
        msgConnection(cid, "Cannot join this session. Game has already started.");
        return ;
    } 

    if (cid == owner.getConnectionID())
        return ;

    int maxPlayersAllowed = configurations.getMaxNoOfPlayers();

    // Find the userType of the new connection.
    UserType userType = UserType::Player;
    if (newUserType == NewUserType::Default) {
        // Max players allowed. if the number of session users is more than
        // this they will be added as audience.
        userType = getUserCountWithType(UserType::Player) < maxPlayersAllowed 
            ? UserType::Player : UserType::Audience;
    } else if (newUserType == NewUserType::Player) {
        int playerCount = getUserCountWithType(UserType::Player);
        if (playerCount < maxPlayersAllowed ){
            userType = UserType::Player;
        } else {
            // if no new player can be added, show an error message to the user.
            msgConnection(cid, MSG_NO_ROOM_FOR_PLAYER);
            return ;
        } 
    } else if (newUserType == NewUserType::Audience) {
        userType = UserType::Audience;
    }
    
    UserIdType userId = static_cast<UserIdType>(sessionUsers.size());
    User user {userName, userId, cid, userType};
    sessionUsers.push_back(user);
    addUserToState(user);

    // Send messgae to owner informing a new user in session.
    std::string userTypeStr = UserType::Player == userType ? "Player" : "Audience";
    std::ostringstream stream;
    stream << userName << " joined as a " << userTypeStr;
    msgConnection(owner.getConnectionID(), stream.str());

    // Send message to client to inform connection status
    stream.str("");
    stream.clear();
    stream << "Connected to session: " << sessionID << "\n";
    msgConnection(cid, stream.str());
}

void 
GameSession::addUserToState(const User& user){
    std::cout << "adding state" << std::endl;

    auto nameVariable = std::make_shared<game::Variable>();
    nameVariable->varType = VariableType::StringType;
    nameVariable->stringVar = user.getName();

    auto idVariable = std::make_shared<game::Variable>();
    idVariable->varType = VariableType::StringType;
    idVariable->stringVar = std::to_string(user.getId());

    if (user.getUserType() == UserType::Player){
        auto playerState = std::make_shared<Variable>();
        auto variableCloner = game::VariableCloner();
        variableCloner.copyVariables(initialState.perPlayer, playerState);

        playerState->mapVar["name"] = nameVariable;
        playerState->mapVar["id"] = idVariable;

        auto players = currentState.variables->getVariable("players");
        players->listVar.emplace_back(playerState);
    } else if (user.getUserType() == UserType::Audience){
        auto audienceState = std::make_shared<Variable>();
        auto variableCloner = game::VariableCloner();
        variableCloner.copyVariables(initialState.perPlayer, audienceState);

        audienceState->mapVar["name"] = nameVariable;
        audienceState->mapVar["id"] = idVariable;
    
        auto audiences = currentState.variables->getVariable("audiences");
        audiences->listVar.emplace_back(audienceState);
    }
}

void 
GameSession::startGame(const ConnectionID& cid){
    if (cid == owner.getConnectionID()){
        if (getUserCountWithType(UserType::Player) >= configurations.getMinNoOfPlayers()){
            gameStarted = true;
            initializeGameState();
            std::string msg = "Game started";
            sessionBroadCast(msg);
        } else {
            std::ostringstream stream;
            stream << "Error starting the game. Minimum number of players needed: "
                << configurations.getMinNoOfPlayers();
            std::string errorMsg = stream.str();
            LOG(INFO) << errorMsg;
            msgConnection(cid, errorMsg);
        }
    } else {
        std::string errorMsg = "Error starting the game. Only the owner can start the game";
        LOG(INFO) << errorMsg;
        msgConnection(cid, errorMsg);
    }
}

std::vector<User> 
GameSession::getPlayers() {
    return getUsersWithType(UserType::Player);
}

std::vector<User> 
GameSession::getAudience() {
    return getUsersWithType(UserType::Audience);
}

std::vector<User> 
GameSession::getUsersWithType(const UserType& userType) {
    std::vector<User> users;

    std::copy_if(sessionUsers.begin(), sessionUsers.end(), std::back_inserter(users),
        [&userType](User& user) { return user.getUserType() == userType;}
    );
    
    return users;
}

int 
GameSession::getUserCountWithType(const UserType& userType){
    return std::count_if(sessionUsers.begin(), sessionUsers.end(), 
        [&userType ](User& user) { return user.getUserType() == userType; }
    );
}

void 
GameSession::setGlobalTimeout(){
    // TODO: implementation.
}

void 
GameSession::setTimeout(UserIdType id, Time delay){
    Time currentTime;
    std::time(&currentTime);
    timeoutMap.emplace(id, currentTime + delay);
}

bool
GameSession::checkTimeOuts(){
    bool allResponsesAvailable = std::all_of(currentState.messageMap.begin(),
        currentState.messageMap.end(),
        [] (const auto& message) { return message.second.length() > 0; }
    );

    if (allResponsesAvailable) 
        return true;

    Time currentTime;
    std::time(&currentTime);
    
    return std::all_of(timeoutMap.begin(), timeoutMap.end(),
        [currentTime] (const auto& timeMap) { return timeMap.second > currentTime; }
    );    
}

void 
GameSession::initializeGameState(){
    moveVariable(initialState.gameVariables);
    moveVariable(initialState.constants);
}

void 
GameSession::moveVariable(std::shared_ptr<Variable> from){
    auto variableCloner = game::VariableCloner();
    auto variable = std::make_shared<Variable>();
    variableCloner.copyVariables(from, variable);

    for (auto& var : variable->mapVar){
        currentState.variables->createVariable(var.first, std::move(var.second));
    }
}