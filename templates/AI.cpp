
#include "AI.h"

AI::AI()
{
    ;
}

std::string AI::username()
{
   return "username";
}

std::string AI::password()
{
   return "password";
}

bool AI::init()
{
   return true;
}

bool AI::end()
{
   return true;
}

bool AI::run()
{
    //debug code [GAME SPECIFIC; BAD REMOVE IT LATER]
    if(bases.size() > 0)
        bases[0].spawn(1);
   return true;
}
