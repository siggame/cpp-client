#ifndef GAME_H
#define GAME_H

#include <string>
#include "network.h"

class Game
{
    public:
    Game();

    void connect(GameSocket conn, std::string addr, int port, std::string name);
    void recieve();
    void wait_for(/*???*/);
    void login();
    void create_game();
    void recv_player_id();
    void init_main();
    void end_main();
    void main_loop();
    void get_log();
    void update_game(/*???*/);
    void change_add(/*???*/);
    void change_remove(/*???*/);
    void change_update(/*???*/);
    void change_global_update(/*???*/);
    void run();
};

#endif
