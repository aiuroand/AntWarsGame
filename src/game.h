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
    /*! Constructor 
     *  @param name    - represents current game's map's filename
     *  @param saves   - represents directory to save maps
     *  @param talents - represents directory that contains talents descriptions
     *  @param scr     - pointer to output screen
     */
    CGame ( std::string name,
            std::string saves,
            std::string talents,
            CScreen * scr )
    : m_Map ( name, scr ),
      m_Saves ( saves ),
      m_Talents ( talents ),
      m_Screen ( scr )
    {}

    /*! Destructor that deallocates allocated resourses
     */
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

    /*! Main loop that runs the game
     */
    void loop ( void );

    /*! Reads talents' names, descriptions and bonuses from m_Talents directory.
     *  Also reads information about rounds, when talents should be suggested to players
     */
    void readTalents( void );
    
    /*! Function that uses information from m_Map to assign talents from saved
     *  map to players
     */
    void setPlayers ( void );

    /*! Function that deletes all players that do not own any anthill on the map from m_Players list
     */
    void removeDead( void );

    /*! Function that prints out game hud with information about the game to human player
    */
    void printHud( void );

    /*! Function that is used to save current game's map to m_Saves folder 
     *  @throw CSavingWonGame if player tries to save the game where he or bot already won
     */
    void saveGame ( void );

  private:
    
    CMap m_Map;
    std::string m_Saves;
    std::string m_Talents;
    CScreen * m_Screen;
    std::list < CPlayer * > m_Players;
    //! std::list that represent tier 1 talents
    std::list < CTalent * > m_Tier1;
    //! std::list that represent tier 2 talents
    std::list < CTalent * > m_Tier2;
    //! std::list that represent tier 3 talents
    std::list < CTalent * > m_Tier3;
    //! Round when tier 1 talent should be suggested to players
    int m_Tier1Time;
    //! Round when tier 2 talent should be suggested to players
    int m_Tier2Time;
    //! Round when tier 3 talent should be suggested to players
    int m_Tier3Time;     
};

#endif // GAME_H