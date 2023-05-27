#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class CPlayer
{
  public:
    CPlayer ( char color )
    : m_Color ( color )
    {};
    virtual ~CPlayer( void ) = default;
    virtual std::pair < int, int > makeMove ( CMap & map ) = 0; 
    char getColor ( void ) const 
    {
      return m_Color;
    }
  protected:
    char m_Color;
};

#endif // PLAYER_H