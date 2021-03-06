#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

//Forward decleration because of cyclical dependencies
class Game;

#include "network.h"
#include <string>

class GameObject
{
    public:
    GameObject(){}
};

##
## S 1 FOR MODEL IN MODELS -----------------------------------------------------
% for model in models:
/// @class ${model.name}
% if model.doc:
///  @brief ${model.doc}
% endif
## ---------------------------------------------------------------- model.parent
% if model.parent:
class ${model.name} : public ${model.parent.name}
% else:
class ${model.name} : public GameObject
% endif
{
## ----------------------------------------------------------- model Constructor
    public:
    ${model.name}(GameSocket* connection, Game* parent_game\
## put all members in the constructor
% for datum in model.data:
, ${type_convert(datum.type)} ${datum.name}\
% endfor
);
## ----------------------------------------------------------- Empty Constructor
    ${model.name}(){}
## S 2 FOR FUNC IN FUNCTIONS ---------------------------------------------- func
## -------------------------------------------- model.$(func.name}(${func.args})
##assume that everything is a bool right now because Russley said to
% for func in model.functions + model.properties:
    /// @fn ${func.name}
% if func.doc:
    ///  @brief ${func.doc}
% endif
% for args in func.arguments:
% if args.doc:
    ///  @param ${args.name} ${args.doc}
% endif
% endfor
    bool ${func.name}(\
% for args in func.arguments:
%   if args == func.arguments[0]:
${type_convert(args.type)} ${args.name}\
%   else:
, ${type_convert(args.type)} ${args.name}\
%   endif
% endfor
);
% endfor

##getters
% for datum in model.data:
    ${type_convert(datum.type)} get_${datum.name}();
% endfor

    //protected:
    GameSocket* connection;
    Game* parent_game;
##enlosed data
% for datum in model.data:
    ${type_convert(datum.type)} ${datum.name};
% endfor

};

## E 2 FOR FUNC IN FUNCTIONS ---------------------------------------------- func
##
% endfor

#endif
