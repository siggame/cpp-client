#include "GameObjects.h"

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
##  put garbage here
    ;
}
% endfor

% endfor

