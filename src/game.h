#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "screen.h"

class CGame
{
  public:
    CGame ( std::string name,
            CScreen * scr )
   : m_Map ( name, scr ),
     m_Screen ( scr )
  {}
    
    void loop ( void );
  private:
    CMap m_Map;
    CScreen * m_Screen;

};

#endif // GAME_H