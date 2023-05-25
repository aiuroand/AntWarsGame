#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>
#include <iostream>
#include "coords.h"

class CScreen
{
  public:

    CScreen ( void )
  {
    initscr();
    m_Window = newwin ( 30, 100, 0, 0 );
    keypad ( m_Window, true );
    nodelay ( m_Window, true );
    curs_set( 0 );
    noecho();
    box ( m_Window, 0, 0 ); 
    start_color();
    init_pair ( 1, COLOR_BLACK, COLOR_GREEN );   
    init_pair ( 2, COLOR_BLACK, COLOR_WHITE );   
  }
    ~CScreen ( void )
  {
    delwin ( m_Window );
    endwin();
  }
  void screenRefresh ( void )
  {
    wrefresh ( m_Window );
    refresh();
  }
  void screenClear ( void )
  {
    wclear( m_Window );
    clear();
  }
  void screenBox ( void )
  {
    box ( m_Window, 0, 0 );
  }
  void screenPrint ( CCoords coord, std::string str )
  {
    mvwprintw( m_Window, coord . m_Y, coord . m_X, "%s", str . c_str() );
  }
  void screenPrint ( CCoords coord, char c )
  {
    mvwprintw( m_Window, coord . m_Y, coord . m_X, "%c", c );
  }
  WINDOW * m_Window;
};

#endif