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
    virtual std::pair < int, int > makeMove ( CMap & map ) = 0; 
    virtual void selectTalent (  CMap & map, std::list < CTalent * > & t ) = 0;
    virtual void activateTalents ( char c, CMap & map ) = 0;
    char getColor ( void ) const 
    {
      return m_Color;
    }
  protected:
    char m_Color;
    std::list < CTalent * > m_Talents;
};

#endif // PLAYER_H