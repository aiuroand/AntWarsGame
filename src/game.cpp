#include "game.h"

void CGame::loop ( void )
{
  m_Map . print();
  std::list < std::pair < int, int > > orders;
  for ( const auto & it : m_Map . m_Players )
    if ( it == 'g' ) 
      m_Players . push_back ( new CHuman ( it, m_Screen ) );
  while ( 1 )
  {
    for ( const auto & it : m_Players )
      orders . push_back ( it -> makeMove( m_Map ) );
    m_Map . print();
  }
}
