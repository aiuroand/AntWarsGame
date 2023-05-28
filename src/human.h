#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include "coords.h"
#include "ncurses.h"
#include "screen.h"
#include "map.h"
#include "exceptions.h"

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
    void selectTalent ( CMap & map, std::list < CTalent * > & t ) override;
  private:
    CScreen * m_Screen;
};
#endif // HUMAN_H