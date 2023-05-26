#include "game.h"

void CGame::loop ( void )
{
  m_Map . print();
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