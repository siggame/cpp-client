#include "GameObjects.h"
#include "json/json.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include <string>

const std::string function_call =
"{\"type\": \"command_name\", \"args\": {\"actor\": 0}}";

##each class
% for model in models:
##constructor
${model.name}::${model.name}(GameSocket* connection, Game* parent_game\
% for datum in model.data:
, ${type_convert(datum.type)} ${datum.name}\
% endfor
)
{
    this->connection = connection;
    this->parent_game = parent_game;
##set each thing equal to itself
% for datum in model.data:
    this->${datum.name} = ${datum.name};
% endfor
}

##all other functions for that class
% for func in model.functions + model.properties:
bool ${model.name}::${func.name}(\
% for args in func.arguments:
%   if args == func.arguments[0]:
${type_convert(args.type)} ${args.name}\
%   else:
, ${type_convert(args.type)} ${args.name}\
%   endif
% endfor
)
{
    std::stringstream convert;
    Json::Value root;
    Json::Reader reader_login;
    reader_login.parse(function_call,root,false);
    root["type"] = ${double_quotes(repr(func.name))};
    root["args"]["actor"] = id;
%   for args in func.arguments:
    convert << ${args.name};
    root["args"][${double_quotes(repr(args.name))}] = convert.str();
    convert.str(std::string());
%   endfor

    convert << root;
    std::cout << root << std::endl;

    connection->send_string(convert.str());
    bool recievedStatus = false;
    bool status;

    while(!recievedStatus)
    {
        std::string message = connection->rec_string();
        Json::Value root2;
        Json::Reader reader_login2;
        reader_login2.parse(function_call,root2,false);
        if(root2["type"] == "success")
        {
            recievedStatus = true;
            status = true;
        }
        else if(root2["type"] == "failure")
        {
            recievedStatus = true;
            status = false;
        }
        else if(root2["type"] == "changes")
        {
            parent_game->update_game(message);
        }
    }
    return status;
}
% endfor

##define getters
% for datum in model.data:
${type_convert(datum.type)} ${model.name}::get_${datum.name}()
{
% if is_primitive(datum.type):
    return ${datum.name};
% else:
    ##some sort of garbage here
% endif
}

% endfor

% endfor

