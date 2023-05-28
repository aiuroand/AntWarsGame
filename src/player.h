#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "talent.h"


class CPlayer
{
  public:
    CPlayer ( char color )
    : m_Color ( color )
    {};
    virtual ~CPlayer( void ) = default;
    char getColor ( void ) const 
    {
      return m_Color;
    }
    void activateTalents ( char c, CMap & map )
    {
      for ( const auto & it : m_Talents )
        it -> activate( c, map );
    }
    void addTalent ( CTalent * t )
    {
      m_Talents . push_back ( t );
    }
    size_t getTalentsSize ( void ) const 
    {
      return m_Talents . size();
    }
    int countTalents ( std::list < CTalent * > & m_Tier1,
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
  
    virtual std::pair < int, int > makeMove ( CMap & map ) = 0; 
    virtual void selectTalent (  CMap & map, std::list < CTalent * > & t ) = 0;
  protected:
    char m_Color;
    std::list < CTalent * > m_Talents;
};

#endif // PLAYER_H