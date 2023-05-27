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
    void selectTalent (  CMap & map, std::list < CTalent * > & t ) override;
    void activateTalents ( char c, CMap & map ) override
    {
      for ( const auto & it : m_Talents )
        it -> activate( c, map );
    }
  private:
    CScreen * m_Screen;
};
#endif // BOT_H