#include "screen.h"

  CScreen::CScreen ( void )
{
  m_Window = initscr(); 
  box ( m_Window, 0, 0 );
}