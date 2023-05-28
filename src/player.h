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
    virtual std::pair < int, int > makeMove ( CMap & map ) = 0; 
    virtual void selectTalent (  CMap & map, std::list < CTalent * > & t ) = 0;
  // protected:
    char m_Color;
    std::list < CTalent * > m_Talents;
};

#endif // PLAYER_H