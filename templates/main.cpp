
#include <iostream>
#include "network.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int ac, char* av[])
{
   bool verbose = false, veryVerbose = false;

   //set up options and stuff
   po::options_description desc("C++ client for SIG-GAME framework");
   desc.add_options()
      ("address,a", po::value<std::string>()->default_value("localhost"),
         "The address of the game server.")
      ("port,p",po::value<int>()->default_value(19000),
         "The port of the game server.")
      ("game,g",po::value<std::string>()->default_value(""),
         "The name of game to connect to on the server.")
      ("verbose,v",
         "Print more output messages.")
      ("very-verbose,V",
         "Print even more output messages.")
      ("help,h",
         "Displays this message");
   ;

   //extract options
   po::variables_map vm;
   po::store(po::parse_command_line(ac, av, desc), vm);
   po::notify(vm);

   //display the description if help is needed
   if(vm.count("help"))
   {
      std::cout<<desc<<std::endl;
      return 1;
   }

   //set verbose/very verbose
   if(vm.count("verbose"))
   {
      std::cout<<"Verbose mode."<<std::endl;
      verbose = true;
   }
   if(vm.count("very-verbose"))
   {
      std::cout<<"Very-verbose mode."<<std::endl;
      veryVerbose = true;
   }

   //set up connection
   GameSocket connection;
   std::string address = vm["address"].as<std::string>();
   int port = vm["port"].as<int>();
   if(connection.open_server_connection(address,port))
   {
      //opened up correctly
   }
   else
   {
      //failed
      std::cout<<"Unable to connect to server."<<std::endl;
   }

   //connection closes automatically
}
