#include <iostream>
#include <fstream>
#include "loop.h"


int main ( void )
{
  std::ifstream ifs ( "conf.txt", std::ios::in );
  std::string maps, saves, talents;

  std::getline ( ifs, maps );
  std::getline ( ifs, saves );
  std::getline ( ifs, talents );
  
  CLoop l ( maps, saves, talents );

  return EXIT_SUCCESS;
}