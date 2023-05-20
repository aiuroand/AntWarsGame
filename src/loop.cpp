#include "loop.h"

void CLoop::loop ( void )
{
  while ( 1 )
  {
    if ( m_Status == e_Menu )
    {
      m_Menu . loop();
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