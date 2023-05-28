#include <iostream>
#include <fstream>
#include "loop.h"

int main ( void )
{
  // File that contains configuraion file
  std::ifstream ifs ( "examples/conf.conf", std::ios::in ); 
  std::string maps, saves, talents, rules;

  std::getline ( ifs, maps );
  std::getline ( ifs, saves );
  std::getline ( ifs, talents );
  std::getline ( ifs, rules );
  
  if ( ifs . bad() || ifs . fail() )
  {
    std::cout<<"Error while reading config file"<<std::endl;
    return EXIT_FAILURE;
  }

  // Entering main loop of all program
  CLoop l ( maps, saves, talents, rules );

  return EXIT_SUCCESS;
}