#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>

class CScreen
{
  public:
      CScreen ( void );
  private:
    WINDOW * m_Window;
};

#endif