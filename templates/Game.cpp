#include "Game.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

std::string Game::receive()
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

std::string Game::wait_for(std::vector<std::string>& types)
{
    while(true)
    {
        std::string message = conn.rec_string();
        Json::Value root;
        Json::Reader reader;
        reader.parse(message,root,false);
        for(int i = 0; i < types.size(); i++)
        {
            if(root["type"].asString() == types[i])
            {
                return message;
            }
        }
    }
}

const std::string login_string =
"{\"type\": \"login\", \"args\": {\"username\": \"\", \"password\": \"\", \"connection_type\": ${fix_name(repr(name))}}}";

bool Game::login()
{
    Json::Value event;
    Json::Reader reader_login;
    reader_login.parse(login_string,event,false);

    event["args"]["username"] = ai.username();
    event["args"]["password"] = ai.password();

    std::stringstream converter;
    std::string login_message;

    //event.asString() does not work
    converter<<event<<std::endl;
    login_message = converter.str();

    std::cout<<"sending: "<<login_message<<std::endl;

    conn.send_string(login_message);

    std::vector<std::string> wanted;
    wanted.push_back("success");
    wanted.push_back("failure");

    std::string message = wait_for(wanted);

    Json::Value root;
    Json::Reader reader;
    reader.parse(message,root,false);
    if(root["type"].asString() == "success")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//create game constant stuff
const std::string create_game_string =
"{\"type\": \"join_game\", \"args\": {}}";

bool Game::create_game()
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(create_game_string,root,false);
    root["args"]["game_name"] = name;

    std::stringstream converter;
    std::string messageSend;
    converter << root;
    messageSend = converter.str();

    std::cout<<"sent: "<<messageSend<<std::endl;

    conn.send_string(messageSend);

    std::vector<std::string> wanted;
    wanted.push_back("success");
    wanted.push_back("failure");

    std::string message = wait_for(wanted);

    Json::Value root2;
    Json::Reader reader2;
    reader.parse(message,root2,false);

    if(root2["type"] == "success")
    {
        name = root2["args"]["name"].asString();
        std::cout<<"Game created: "<<name<<std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::recv_player_id()
{
    std::vector<std::string> wanted;
    wanted.push_back("player_id");

    wait_for(wanted);
    return true;
}

bool Game::init_main()
{
    std::vector<std::string> wanted;
    wanted.push_back("start_game");
    wait_for(wanted);

    ai.init();
    return true;
}

bool Game::end_main()
{
    ai.end();
    return true;
}

const std::string end_turn_string =
"end_turn = {\"type\": \"end_turn\", \"args\": {}}";

bool Game::main_loop()
{
    std::vector<std::string> wanted;
    wanted.push_back("start_turn");
    wanted.push_back("game_over");

    while(true)
    {
        std::string message = wait_for(wanted);
        Json::Value root;
        Json::Reader reader;
        reader.parse(message,root,false);

        if(root["type"] == "game_over")
        {
            return true;
        }

        if(ai.my_player_id == ai.player_id)
        {
            std::cout<<"Turn Number: "<<ai.turn_number<<std::endl;
            ai.run();
            conn.send_string(end_turn_string);
        }
    }
}

const std::string get_log_string =
"get_log = {\"type\": \"get_log\", \"args\": {}}";

bool Game::get_log()
{
    conn.send_string(get_log_string);

    std::vector<std::string> wanted;
    wanted.push_back("success");
    wanted.push_back("failure");

    std::string message = wait_for(wanted);
    Json::Value root;
    Json::Reader reader;
    reader.parse(message,root,false);

    if(root["type"] == "success")
    {
        std::string fileName = name + ".glog";
        std::ofstream fout;
        fout.open(fileName.c_str());
        fout << root["args"]["log"].asString();
        fout.close();
    }
}

bool Game::update_game(std::string message)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(message,root,false);

    if(root["type"] != "changes")
        return false;

    Json::Value changes = root["args"]["changes"];

    for(int i = 0; i < changes.size(); i++)
    {
        if(changes[i]["action"].asString() == "add")
        {
            change_add(changes[i].asString());
        }
        else if(changes[i]["action"].asString() == "remove")
        {
            change_remove(changes[i].asString());
        }
        else if(changes[i]["action"].asString() == "update")
        {
            change_update(changes[i].asString());
        }
        else if(changes[i]["action"].asString() == "global_update")
        {
            change_global_update(changes[i].asString());
        }
    }
    return true;
}

bool Game::change_add(std::string change)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(change,root,false);

    Json::Value values = root["values"];
    if(false){}
% for model in models:
% if model.type == "Model":
    else if(root["type"].asString() == "${model.name}")
    {
        ${model.name} temp(&conn,this\
% for datum in model.data:
, values["${datum.name}"].as${type_convert2(datum.type)}()\
% endfor
);
        ai.${lowercase(model.plural)}.push_back(temp);
    }
% endif
% endfor
    else
    {
        std::cout<<"Unknown model attempted to add!!"<<std::endl;
    }
    return true;
}

bool Game::change_remove(std::string change)
{
    return true;
}

bool Game::change_update(std::string change)
{
    return true;
}

bool Game::change_global_update(std::string change)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(change,root,false);

    Json::Value values = root["values"];
    for(int i = 0;i < root.size(); i++)
    {
        //Hey this code looks funny, I wonder why?
        //[Note that this was the original]
        if(false){}
% for datum in globals:
        else if(root[i].asString() == "${datum.name}")
        {
            ai.${datum.name} = values[i]["${datum.name}"].as${type_convert2(datum.type)}();
        }
% endfor
        else
        {
            std::cout<<"Error: Unknown global update!!"<<std::endl;
        }
    }
    return true;
}

bool Game::run()
{
    std::string game_over_message;
    if(!connect())
    {
        return false;
    }
    if(!login())
    {
        return false;
    }
    if(!create_game())
    {
        return false;
    }
    if(!recv_player_id())
    {
        return false;
    }
    if(!init_main())
    {
        return false;
    }

    try
    {
        main_loop();
    }
    catch(GameOverException e)
    {
        if(e.winner == ai.my_player_id)
        {
            game_over_message = "You Win! - " + e.reason;
        }
        else
        {
            game_over_message = "You Lose! - " + e.reason;
        }
    }
    catch(...)
    {
        game_over_message = "Game over was never reached.";
    }

    if(!end_main())
    {
        return false;
    }

    std::cout<<game_over_message<<std::endl;

    if(!get_log())
    {
        return false;
    }
    return true;
}
