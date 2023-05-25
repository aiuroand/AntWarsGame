#include "anthill.h"

int CAntHill::getColor( void )
{
  if ( m_Color == 'g' )
    return 1;
  else if ( m_Color == 'w' )
    return 2;
}

void CAntHill::print ( CScreen * scr )
{
  int c = getColor();
  wattron( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y, m_Coords . m_X, "%s", "******" );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X, "%c", '*' );
  wattroff( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 1, "%s", "T+" );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 3, "%d", m_Ants / 10 );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 4, "%d", m_Ants % 10 );
  wattron( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 5, "%c", '*' );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 2, m_Coords . m_X, "%s", "******" );
  wattroff( scr -> m_Window, COLOR_PAIR ( c ) );
}