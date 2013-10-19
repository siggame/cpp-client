
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "network.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    int verbosity = 0;
    std::string conn_addr = "localhost";
    std::string game_name = "None";
    int conn_port = 19000;

    if(argc == 4) //run [address] [game_name] [verbosity]
    {
        conn_addr = argv[1];
        game_name = argv[2];
        if(strcmp(argv[3], "1") == 0 )
            verbosity = 1;
        else if(strcmp(argv[3], "2") == 0)
            verbosity = 2;
    }
    else if(argc == 3) //run [address] [game_name]
    {
        conn_addr = argv[1];
        game_name = argv[2];
    }
    else if(argc == 2) //run [game_name]
    {
        game_name = argv[1];
    }
    else
    {
        std::cout << "run [address] [game_name] [verbosity (1,2)]" << std::endl;
        std::cout << "run [address] [game_name]" << std::endl;
        std::cout << "run [game_name]" << std::endl;
        exit(1);
    }

    std::cout << "address: " << conn_addr << std::endl;
    std::cout << "port: " << conn_port << std::endl;
    std::cout << "game name: " << game_name << std::endl;
    std::cout << "verbosity: " << verbosity << std::endl;

    //set up connection
    GameSocket connection;
    /*if(!connection.open_server_connection(conn_addr,conn_port))
        std::cout << "Unable to connect to server." << std::endl;*/

    Game game(connection, conn_addr, conn_port, game_name);

    game.connect();
    game.run();

    //connection closes automatically
    return 0;
}
