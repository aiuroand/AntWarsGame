#include "loop.h"

void CLoop::loop ( void )
{
  while ( 1 )
  {
    if ( m_Status == e_Menu )
    {
      m_Menu . loop();
    }
  }

}