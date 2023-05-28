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
      case 10:  // Enter pressed ( I dont understand why KEY_ENTER does not work )
        if ( m_Highlight == 0 )
          chooseNewMap();
        else if ( m_Highlight == 1 )
          continueMap();
        else if ( m_Highlight == 2 )
          m_Status = e_Rules;
        else if ( m_Highlight == 3 )
          m_Status = e_Exit;
        return;
      default:
        break;
    }
  }
}

void CMenu::chooseNewMap( void )
{
  int choise = 0;
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  m_Screen -> screenBox();
  while ( 1 )
  {
    int i = 0;
    for ( const auto & it : std::filesystem::directory_iterator( m_Maps ) )
    { 
      if ( i == m_HighlightMaps )
        wattron ( m_Screen -> m_Window , A_REVERSE );
      mvwprintw ( m_Screen -> m_Window, i+5, 5, ( it . path() . c_str() + m_Maps . size() + 1 ) );
      wattroff ( m_Screen -> m_Window, A_REVERSE );
      i++;
    }
    if ( i == 0 )
      return;
    choise = wgetch ( m_Screen -> m_Window );
    switch ( choise )
    {
      case KEY_UP:
        m_HighlightMaps --;
        if ( m_HighlightMaps == -1 )
          m_HighlightMaps = i - 1;
        break;
      case KEY_DOWN:
        m_HighlightMaps++;
        if ( m_HighlightMaps == i )
          m_HighlightMaps = 0;
        break;
      case 'q': 
        m_Status = e_Menu;
        return;
      case 10:  // Enter pressed ( I dont understand why KEY_ENTER does not work )
        m_Status = e_NewGame;
        return;
      default:
        break;
    }
  }
}

void CMenu::continueMap( void )
{
  int choise = 0;
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  m_Screen -> screenBox();

  while ( 1 )
  {
    int i = 0;
    for ( const auto & it : std::filesystem::directory_iterator( m_Saves ) )
    { 
      if ( i == m_HighlightSaves )
        wattron ( m_Screen -> m_Window , A_REVERSE );
      mvwprintw ( m_Screen -> m_Window, i+5, 5, ( it . path() . c_str() + m_Saves . size() + 1 ) );
      wattroff ( m_Screen -> m_Window, A_REVERSE );
      i++;
    }
    if ( i == 0 )
      return;
    choise = wgetch ( m_Screen -> m_Window );
    switch ( choise )
    {
      case KEY_UP:
        m_HighlightSaves --;
        if ( m_HighlightSaves == -1 )
          m_HighlightSaves = i - 1;
        break;
      case KEY_DOWN:
        m_HighlightSaves++;
        if ( m_HighlightSaves == i )
          m_HighlightSaves = 0;
        break;
      case 'q': 
        m_Status = e_Menu;
        return;
      case 10:  // Enter pressed ( I dont understand why KEY_ENTER does not work )
        m_Status = e_ContinueGame;
        return;
      default:
        break;
    }
  }

}