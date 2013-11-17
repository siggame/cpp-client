
#include "AI.h"
#include <iostream>

std::string AI::username()
{
   return "username";
}

std::string AI::password()
{
   return "password";
}

/// @fn init
///  @breif Initialization function that is ran before the game begins.
bool AI::init()
{
   return true;
}

/// @fn end
///  @breif Ending function that is ran after the game ends.
bool AI::end()
{
   return true;
}

/// @fn run
///  @breif Function is ran for each turn.
bool AI::run()
{
   return true;
}
