#include "menu.h"

void CMenu::loop ( )
{
  int choise = 0;
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  m_Screen -> screenBox();
  while ( 1 )
  {
    
    for ( int i = 0; i < 4; i++ )
    { 
      if ( i == m_Highlight )
        wattron ( m_Screen -> m_Window , A_REVERSE );
      mvwprintw ( m_Screen -> m_Window, i+5, 5, ( m_Elements[i] . c_str() ) );
      wattroff ( m_Screen -> m_Window, A_REVERSE );
    }
    choise = wgetch ( m_Screen -> m_Window );
    switch ( choise )
    {
      case KEY_UP:
        m_Highlight --;
        if ( m_Highlight == -1 )
          m_Highlight = m_Elements . size() - 1;
        break;
      case KEY_DOWN:
        m_Highlight++;
        if ( (size_t) m_Highlight == m_Elements . size() )
          m_Highlight = 0;
        break;
      default:
        break;
    }
    if ( choise == 10 ) // Enter pressed
    {
      if ( m_Highlight == 2 )
        m_Status = e_Rules;
      else if ( m_Highlight == 3 )
        m_Status = e_Exit;
      break;
    }
  }
}