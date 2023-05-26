#include "human.h"
std::pair < int, int > CHuman::makeMove ( CMap & map )
{
  int first, second;
  while ( 1 )
  {
    CCoords mouseCoords = readMouse();
    if ( ( first = map . getAntHill ( mouseCoords ) ) != -1
       && map . getColorOfId ( first ) == 'g' )
      break;
  }
  mvwprintw( m_Screen -> m_Window, 1, 42, "%d", first );
  wrefresh ( m_Screen -> m_Window );
  while ( 1 )
  {
    CCoords mouseCoords = readMouse();
    if ( ( second = map . getAntHill ( mouseCoords ) ) != -1
        && second != first )
      break;
  }

  mvwprintw( m_Screen -> m_Window, 1, 44, "%d", second );
  wrefresh ( m_Screen -> m_Window );
  return std::make_pair( first, second );
}

CCoords CHuman::readMouse( void )
{
  MEVENT event;
  int c;
  while ( 1 )
  {
    c = wgetch( m_Screen -> m_Window );
    switch ( c )
    {
      case KEY_MOUSE:
        if(getmouse(&event) == OK && ( event . bstate == BUTTON1_CLICKED
                                    || event . bstate == BUTTON1_DOUBLE_CLICKED
                                    // || event . bstate == BUTTON1_RELEASED    
                                    || event . bstate == BUTTON1_TRIPLE_CLICKED
                                    || event . bstate == BUTTON1_PRESSED ) )
          return CCoords ( event . x, event . y );
      default:
        continue;
    }
  }
}