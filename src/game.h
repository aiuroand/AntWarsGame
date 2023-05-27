#ifndef GAME_H
#define GAME_H
#include "map.h"
#include <set>
#include "screen.h"
#include "player.h"
#include "human.h"
#include "bot.h"
#include <chrono>
#include <thread>
// #include "anthill.h"

class CGame
{
  public:
    CGame ( std::string name,
            CScreen * scr )
   : m_Map ( name, scr ),
     m_Screen ( scr )
  {}
    
    void loop ( void ); 
    void removeDead( void );
  private:
    CMap m_Map;
    CScreen * m_Screen;
    std::list < CPlayer * > m_Players;

};

#endif // GAME_H