#include "loop.h"

void CLoop::loop ( void )
{
  while ( 1 )
  {
    if ( m_Status == e_Menu )
    {
      m_Menu . loop();
    }
    else if ( m_Status == e_NewGame )
    {
      char str[100];
      int i = 0;
      for ( const auto & it : std::filesystem::directory_iterator ( m_Maps ) )
      {
        if ( i == m_Menu . m_HighlightMaps )
        {
          memcpy ( str,
                   it . path() . c_str() + m_Maps . size() + 1,
                   strlen ( it . path() . c_str() + m_Maps . size() + 1 ) + 1 );
          break;
        }
        i++;
      }
      std::string newStr( str );
      m_Game = new CGame ( m_Maps + "/" + newStr, m_Screen );
      m_Game -> loop();
    }
    else if ( m_Status == e_Rules )
    {
      m_Rules . loop();
    }
    else if ( m_Status == e_Exit )
    {
      delete m_Screen;
      return;
    }
  }

}