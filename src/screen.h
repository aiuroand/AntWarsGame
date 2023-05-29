#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>
#include <iostream>
#include "coords.h"

class CScreen
{
  public:

  //! Main window from lncurses
  WINDOW * m_Window;

  /*! Constructing screen and window for the game using lncurses.
   */
  CScreen ( void )
  {
    initscr();
    m_Window = newwin ( 30, 100, 0, 0 ); // new WINDOW pointer object
    keypad ( m_Window, true ); // Allowing KEY_UP and KEY_DOWN buttons
    mousemask ( ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL ); // Allowing mouse events
    nodelay ( m_Window, true );
    curs_set( 0 ); // Invisible cursos
    noecho();
    box ( m_Window, 0, 0 );  // Window default borders 
    start_color(); // Allowing colors using
    init_pair ( 1, COLOR_BLACK, COLOR_GREEN );   // Color of players anthills
    init_pair ( 2, COLOR_BLACK, COLOR_WHITE );   // Color of neutral anthills  
    init_pair ( 3, COLOR_BLACK, COLOR_RED );     // Color of bots anthills
    init_pair ( 4, COLOR_WHITE, COLOR_MAGENTA ); // Color of bots anthills  
    init_pair ( 5, COLOR_WHITE, COLOR_BLUE ); // Color of bots anthills  
  }
  /*! Deleting all alocated lncurses objects
   */
  ~CScreen ( void )
  {
    delwin ( m_Window );
    endwin();
  }
  /*! Actualizing information about m_Window
   */
  inline void screenRefresh ( void )
  {
    wrefresh ( m_Window );
    refresh();
  }
  /*! Removing all objects from m_Window
   */
  inline void screenClear ( void )
  {
    wclear( m_Window );
    clear();
  }
  /*! Printing default borders to m_Window
   */
  inline void screenBox ( void )
  {
    box ( m_Window, 0, 0 );
  }
  /*! Printing std::string objekt to m_Window
   *  @param coords - coordinates where printed object has to start from
   *  @param str    - string to print
   */
  inline void screenPrint ( const CCoords coords, const std::string & str )
  {
    mvwprintw( m_Window, coords . m_Y, coords . m_X, "%s", str . c_str() );
  }
  /*! Printing char objekt to m_Window
   *  @param coords - coordinates where printed object has to be printed
   *  @param str    - char to print
   */
  inline void screenPrint ( const CCoords coords, const char c )
  {
    mvwprintw( m_Window, coords . m_Y, coords . m_X, "%c", c );
  }
};
#endif // SCREEN_H