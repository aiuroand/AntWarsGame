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
    // wmove ( m_Window, coord . m_X, coord . m_Y );
    mvwprintw( m_Window, coord . m_X, coord . m_Y, "%s", str . c_str() );
  }
  WINDOW * m_Window;
};

#endif