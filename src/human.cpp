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

void CHuman::selectTalent ( CMap & map, std::list < CTalent * > & t )
{

  wclear ( m_Screen -> m_Window );
  wrefresh( m_Screen -> m_Window );
  mvwprintw ( m_Screen -> m_Window, 1, 1, "Select new talent:" );

  auto tal1 = t . front();
  mvwprintw ( m_Screen -> m_Window, 3, 1, "1) %s", tal1 -> getName() . c_str() );
  mvwprintw ( m_Screen -> m_Window, 5, 1, "%s", tal1 -> getDescription() . c_str() );
  mvwprintw ( m_Screen -> m_Window, 7, 1, "Select" );

  mvwprintw ( m_Screen -> m_Window, 9, 0, "-----------------------------------------------------------------------" );

  auto tal2 = t . back();
  mvwprintw ( m_Screen -> m_Window, 11, 1, "2) %s", tal2 -> getName() . c_str() );
  mvwprintw ( m_Screen -> m_Window, 13, 1, "%s", tal2 -> getDescription() . c_str() );
  mvwprintw ( m_Screen -> m_Window, 15, 1, "Select" );
  
  while ( 1 )
  {
    CCoords mouseCoords = readMouse();

    if ( mouseCoords . m_Y == 7 && mouseCoords . m_X >= 1 && mouseCoords . m_X <= 6  )
    {
      m_Talents . push_back ( t . front() );
      break;
    }
    if ( mouseCoords . m_Y == 15 && mouseCoords . m_X >= 1 && mouseCoords . m_X <= 6  )
    {
      m_Talents . push_back ( t . back() );
      break;
    }
  }

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
        break;
      case 'q':
        throw CLeave{};
        break;
      case 's':
        throw CSave{};
        break;
      default:
        continue;
    }
  }
}