#ifndef BOT_H
#define BOT_H
#include "player.h"
#include "coords.h"
#include "ncurses.h"
#include "screen.h"
#include "map.h"

class CBot: public CPlayer
{
  public:
    CBot ( char color,
             CScreen * screen )
    : CPlayer( color ),
      m_Screen ( screen )
    {};
    std::pair < int, int > makeMove ( CMap & map ) override;
  private:
    CScreen * m_Screen;
};
#endif // BOT_H