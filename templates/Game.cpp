#include "Game.h"
#include "json/json.h"

Game::Game(GameSocket& conn, std::string addr, int port, std::string name)
{
    this->conn = conn;
    this->addr = addr;
    this->port = port;
    this->name = name;
    ai.connection = conn;
}

bool Game::connect()
{
    return conn.open_server_connection(addr,port);
}

std::string Game::recieve()
{
    std::string message = conn.rec_string();
    Json::Value root;
    Json::Reader reader;
    reader.parse(message,root,false);
    if(root["type"] == "changes")
    {
        update_game(message);
    }
    else if(root["type"] == "player_id")
    {
        ai.my_player_id = root["type"]["id"].asInt();
    }
    else if(root["type"] == "game_over")
    {
        throw GameOverException(root["args"]["winner"].asInt(),
                                root["args"]["reason"].asString());
    }
    return message;
}

std::string Game::wait_for(std::vector<std::string> types)
{
    while(true)
    {
        std::string message = conn.rec_string();
        for(int i = 0; i < types.size(); i++)
        {
            if(message == types[i])
            {
                return message;
            }
        }
    }
}

bool Game::login()
{
    Json::Value event;
    std::string login_message;
    login_message = event.asInt();
}

bool Game::create_game()
{
    ;
}

bool Game::recv_player_id()
{
    ;
}

bool Game::init_main()
{
    ;
}

bool Game::end_main()
{
    ;
}

bool Game::main_loop()
{
    ;
}

bool Game::get_log()
{
    ;
}

bool Game::update_game(std::string message)
{
    ;
}

bool Game::change_add(std::string change)
{
    ;
}

bool Game::change_remove(std::string change)
{
    ;
}

bool Game::change_update(std::string change)
{
    ;
}

bool Game::change_global_update(std::string change)
{
    ;
}

bool Game::run()
{
    ;
}
