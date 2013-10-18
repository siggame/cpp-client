#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "network.h"

class Game
{
    public:
    Game();

    void connect(GameSocket conn, std::string addr, int port, std::string name);
    void recieve();
    void wait_for(std::vector<std::string> types);
    void login();
    void create_game();
    void recv_player_id();
    void init_main();
    void end_main();
    void main_loop();
    void get_log();
    void update_game(std::string message);
    void change_add(std::string change);
    void change_remove(std::string change);
    void change_update(std::string change);
    void change_global_update(std::string change);
    void run();
};

#endif
