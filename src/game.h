#ifndef GAME_H
#define GAME_H

#include <set>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>
#include "screen.h"
#include "player.h"
#include "human.h"
#include "bot.h"
#include "map.h"
#include "talent.h"
#include "moreants.h"
#include "morearmor.h"
#include "moremove.h"
#include "moremax.h"
#include "conqueror.h"
#include "maxants.h"
#include "exceptions.h"

class CGame
{
  public:
    CGame ( std::string name,
            std::string saves,
            std::string talents,
            CScreen * scr )
    : m_Map ( name, scr ),
      m_Saves ( saves ),
      m_Talents ( talents ),
      m_Screen ( scr )
    {}
    ~CGame ( void )
    {
      for ( const auto & it : m_Players )
        delete it;
      for ( const auto & it : m_Tier1 )
        delete it;
      for ( const auto & it : m_Tier2 )
        delete it;
      for ( const auto & it : m_Tier3 )
        delete it;
    }
    
    void loop ( void );
    void readTalents( void );
    void setPlayers ( void );
    void removeDead( void );
    void printHud( void );
    void saveGame ( void );
  private:
    CMap m_Map;
    std::string m_Saves;
    std::string m_Talents;
    CScreen * m_Screen;
    std::list < CPlayer * > m_Players;
    std::list < CTalent * > m_Tier1;
    std::list < CTalent * > m_Tier2;
    std::list < CTalent * > m_Tier3;
    int m_Tier1Time;
    int m_Tier2Time;
    int m_Tier3Time;     
};

#endif // GAME_H