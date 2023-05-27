#include "anthill.h"

#define GREEN 1
#define WHITE 2
#define RED 3
#define MAGENTA 4

void CAntHill::print ( CScreen * scr )
{
  int c;
  if ( m_Color == 'g' )
    c = GREEN;
  else if ( m_Color == 'w' )
    c = WHITE;
  else if ( m_Color == 'r' )
    c = RED;
  else if ( m_Color == 'm' )
    c = MAGENTA;
    
  wattron( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y, m_Coords . m_X, "%s", "*****" );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X, "%c", '*' );
  wattroff( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 1, "%s", "+" );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 2, "%d", m_Ants / 10 );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 3, "%d", m_Ants % 10 );
  wattron( scr -> m_Window, COLOR_PAIR ( c ) );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 1, m_Coords . m_X + 4, "%c", '*' );
  mvwprintw( scr -> m_Window, m_Coords . m_Y + 2, m_Coords . m_X, "%s", "*****" );
  wattroff( scr -> m_Window, COLOR_PAIR ( c ) );
}