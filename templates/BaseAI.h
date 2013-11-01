#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <string>
#include "network.h"
#include "GameObjects.h"

/// @class BaseAI
///  @brief Class to store competitor-accessible data and functions

class BaseAI
{
    public:
    GameSocket connection;
    std::string game_name;

    /// @var my_player_id
    ///  @breif The player_id of the competitor.
    int my_player_id;

%   for datum in globals:
    /// @var ${datum.name}
% if datum.doc:
    ///  @brief ${datum.doc}
% endif
    ${type_convert(datum.type)} ${datum.name};
%   endfor

%   for model in models:
%       if model.type == "Model":
    /// @var ${lowercase(model.plural)}
    ///  @brief List containing all ${model.plural}.
    std::vector<${model.name}> ${lowercase(model.plural)};
%       endif
%   endfor

%   for datum in globals:
    ${type_convert(datum.type)} get_${datum.name}(){return ${datum.name};}
%   endfor

    BaseAI();
};

#endif
