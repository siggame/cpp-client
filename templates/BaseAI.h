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
%       if datum.type == "str":
    std::string ${datum.name};
%       else:
    ${datum.type} ${datum.name};
%       endif
%   endfor

%   for model in models:
%       if model.type == "Model":
    std::vector<${model.name}> ${lowercase(model.plural)};
%       endif
%   endfor

%   for datum in globals:
%       if model.type == "str":
    std::string get_${datum.name}(){return ${datum.name};}
%       else:
    ${datum.type} get_${datum.name}(){return ${datum.name};}
%       endif
%   endfor

    BaseAI();
};

#endif
