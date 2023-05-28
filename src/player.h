#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "talent.h"

/*! Abstract class that represents parent for CBot and CHuman
 */
class CPlayer
{
  public:
    /*! Constructor
     *  @param color - represent color
     */
    CPlayer ( char color )
    : m_Color ( color )
    {};
    
    /*! Destructor that deallocates allocated resourses
     *  @param color - represent color
     */
    virtual ~CPlayer( void )
    {
      for ( const auto & it : m_Talents )
        delete it;
    }

    /*! Gets color of current player
     *  @return players color
     */
    inline char getColor ( void ) const 
    {
      return m_Color;
    }
    
    /*! Activates all talents from m_Talents std::list
     */
    inline void activateTalents ( char c, CMap & map ) const
    {
      for ( const auto & it : m_Talents )
        it -> activate( c, map );
    }

    /*! Adds talent to current player
     *  @param t - pointer to abstract CTalent
     */
    inline void addTalent ( CTalent * t )
    {
      m_Talents . push_back ( t );
    }
    
    /*! Return number of learned talents
     *  @return m_Talents std::list's size
     */
    inline size_t getTalentsSize ( void ) const 
    {
      return m_Talents . size();
    }

    /*! Calculates "Talent integer" for saving
     *  Talent integer - talent tree in my maps and saves files is represented as an integer from 0 to 64
     *  it allows the game to unambiguosly determine what talents current player has. For example
     *  24 is 0b00010111, that means player has 1st, 2nd, 3d and 5th talents.
     *  @return "Talent integer"
     */
    inline int countTalents ( std::list < CTalent * > & m_Tier1,
                              std::list < CTalent * > & m_Tier2,
                              std::list < CTalent * > & m_Tier3 ) const
    {
      int sum = 0;
      for ( const auto & it : m_Talents )
      {
             if ( it -> getName() == m_Tier1 . front() -> getName() )
          sum += 1;
        else if ( it -> getName() == m_Tier1 . back() -> getName() )
          sum += 2;
        else if ( it -> getName() == m_Tier2 . front() -> getName() )
          sum += 4;
        else if ( it -> getName() == m_Tier2 . back() -> getName() )
          sum += 8;
        else if ( it -> getName() == m_Tier3 . front() -> getName() )
          sum += 16;
        else if ( it -> getName() == m_Tier2 . back() -> getName() )
          sum += 32;
      }
      return sum;
    }
    /*! Abstract method that is used to collect moves from all both human and bots players
     *  @param map - current game's map
     *  @return std::pair < int , int > where first number is attacker anthill's id, 
     *                                        second is target anthill's id
     */
    virtual std::pair < int, int > makeMove ( CMap & map ) = 0; 

    /*! Abstract method that allows players to select talents
     *  @param map - current game's map
     *  @param t   - std::list of pointers to abstract CTalent player should choose talent from
     */
    virtual void selectTalent (  CMap & map, std::list < CTalent * > & t ) = 0;

  protected:

    char m_Color;
    std::list < CTalent * > m_Talents;
};

#endif // PLAYER_H