#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

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
## S 2 FOR FUNC IN FUNCTIONS ---------------------------------------------- func
## -------------------------------------------- model.$(func.name}(${func.args})
##assume that everything is a bool right now because Russley said to
% for func in model.functions + model.properties:
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

    protected:
##enlosed data
% for datum in model.data:
    ${type_convert(datum.type)} ${datum.name};
% endfor
};

## E 2 FOR FUNC IN FUNCTIONS ---------------------------------------------- func
##
% endfor

#endif
