#include "game.h"

void CGame::loop ( void )
{
  m_Map . print();
  
  for ( const auto & it : m_Map . m_Players )
    if ( it == 'g' ) 
      m_Players . push_back ( new CHuman ( it, m_Screen ) );
    // else if ( it == 'r' )
      // m_Players . push_back ( new CBot ( it, m_Screen ) );
  while ( 1 )
  {
    std::list < std::pair < int, int > > orders;
  
    for ( const auto & it : m_Players )
      orders . push_back ( it -> makeMove( m_Map ) );

    for ( const auto & it : orders )
    { 
      m_Map . attack( it . first, it . second );
    }
    m_Map . createAnts();
    m_Map . print();
    char c;
    if ( ( c = m_Map . checkWinner() ) != 'n' )
    {
      mvwprintw ( m_Screen -> m_Window, 10, 10, "%c won", c );
      wrefresh( m_Screen -> m_Window );
            std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
      break;
    }
    
  }
}
