#include <iostream>
#include <fstream>
#include "loop.h"
  

int main ( void )
{
  std::ifstream ifs ( "examples/conf.conf", std::ios::in );
  std::string maps, saves, talents, rules;

  std::getline ( ifs, maps );
  std::getline ( ifs, saves );
  std::getline ( ifs, talents );
  std::getline ( ifs, rules );
  
  CLoop l ( maps, saves, talents, rules );

  return EXIT_SUCCESS;
}