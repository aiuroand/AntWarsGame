#ifndef ANTHILL_H
#define ANTHILL_H
#define ANTS_MAX 10
#define ANTS_MOVE 1
#define ANTS_ATTACK 3

#include "mapelement.h"
#include "screen.h"
#include "coords.h"

class CAntHill: public CMapElem
{
  public:
      CAntHill ( CCoords coord,
                 char color,
                 int ants,
                 int id )
     : CMapElem ( color, coord ),
       m_Ants ( ants ),
       m_Id ( id ),
       m_Attack ( ANTS_ATTACK ),
       m_Max ( ANTS_MAX )
    {}
  void print ( CScreen * scr ) override;
  bool isInside ( CCoords coord ) const
  {
    return coord . m_X >= m_Coords . m_X 
        && coord . m_Y >= m_Coords . m_Y
        && coord . m_X <= m_Coords . m_X + 5
        && coord . m_Y <= m_Coords . m_Y + 2;
  }
  int getId ( void ) const 
  {
    return m_Id;
  }
  int getAnts ( void ) const 
  {
    return m_Ants;
  }
  char getColor( void ) const
  {
    return m_Color;
  }
  CCoords getCoords ( void ) const
  {
    return m_Coords;
  }
  int getAttack( void ) const
  {
    return m_Attack <= m_Ants ? m_Attack : m_Ants;
  }
  void setColor( char c )
  {
    m_Color = c;
  }
  void setAnts ( int amount )
  {
    m_Ants = amount;
  }
  void add ( int amount )
  {
    if ( m_Ants + amount < m_Max ) 
      m_Ants += amount;
    else 
      m_Ants = m_Max;
    // if ( amount > 0
    //   && m_Ants == 0 )
    // {
    //   m_Color = 'w';
    //   m_Owner = 'n';
    // }
  }
  void createAnts ( void )
  {
    m_Ants += ANTS_MOVE;
    if ( m_Ants > m_Max )
      m_Ants = m_Max;
  }
  private:
    int m_Ants;
    int m_Id;
    int m_Attack;
    int m_Max;
};
#endif // ANTHILL_H