// #include <iostream>
#include "player.h"
#include "coords.h"
#include "ncurses.h"
#include "screen.h"
#include "map.h"

class CHuman : public CPlayer
{
  public:
    CHuman ( char color,
             CScreen * screen )
    : CPlayer( color ),
      m_Screen ( screen )
    {};
    std::pair < int, int > makeMove ( CMap & map ) override;
    CCoords readMouse ( void );
  private:
    CScreen * m_Screen;
};