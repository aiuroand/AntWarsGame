#include "game.h"

void CGame::loop ( void )
{
  while ( 1 )
  {
    getch();
    readInput();
    m_Map . print();
  }
}

void CGame::readInput ( void )
{

}