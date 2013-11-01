#ifndef AI_H
#define AI_H

#include <string>
#include "BaseAI.h"
#include "network.h"

/// @class AI
///  @brief Class to implement competitor code

class AI : public BaseAI
{
   public:

   AI();

   std::string username();
   std::string password();

    /// @fn init
    ///  @breif Initialization function that is ran before the game begins.
   bool init();

    /// @fn end
    ///  @breif Ending function that is ran after the game ends.
   bool end();

    /// @fn run
    ///  @breif Function is ran for each turn.
   bool run();
};

#endif
