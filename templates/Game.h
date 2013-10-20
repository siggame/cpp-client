#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "AI.h"
#include "network.h"

class GameOverException
{
    public:
    int winner;
    std::string reason;
    GameOverException(int winner, std::string reason):winner(winner),
                                                      reason(reason){}
};

class Game
{
    protected:
    GameSocket conn;
    std::string addr;
    int port;
    std::string name;
    AI ai;

    public:
    Game(GameSocket& conn, std::string addr, int port, std::string name);

    bool connect();
    std::string receive();
    std::string wait_for(std::vector<std::string> types);
    bool login();
    bool create_game();
    bool recv_player_id();
    bool init_main();
    bool end_main();
    bool main_loop();
    bool get_log();
    bool update_game(std::string message);
    bool change_add(std::string change);
    bool change_remove(std::string change);
    bool change_update(std::string change);
    bool change_global_update(std::string change);
    bool run();
};

#endif
