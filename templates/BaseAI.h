#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <string>
#include "network.h"

class BaseAI
{
    public:
    GameSocket connection;
    std::string game_name;
    int my_player_id;

%   for datum in globals:
    ${type_convert(datum.type)} ${datum.name};
%   endfor

%   for model in models:
%       if model.type == "Model":
    std::vector<${model.name}> ${lowercase(model.plural)};
%       endif
%   endfor

%   for datum in globals:
    ${type_convert(datum.type)} get_${datum.name}(){return ${datum.name};}
%   endfor

    BaseAI();
};

#endif
