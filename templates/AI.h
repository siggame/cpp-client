#ifndef AI_H
#define AI_H

#include <string>

class AI : public BaseAI
{
   public:

   AI();

   std::string username();
   std::string password();

   bool init();
   bool end();
   bool run();
}

#endif
