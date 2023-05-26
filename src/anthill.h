#ifndef ANTHILL_H
#define ANTHILL_H
#define ANTS_MAX 10
#include "mapelement.h"
#include "screen.h"
#include "coords.h"

class CAntHill: public CMapElem
{
  public:
      CAntHill ( CCoords coord,
                 int owner,
                 char color,
                 int ants,
                 int id )
     : CMapElem ( owner, coord ),
       m_Ants ( ants ),
       m_Color ( color ),
       m_Id ( id )
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
  void add ( int amount )
  {
    // if ( m_Ants + amount < ANTS_MAX )
      m_Ants += amount;
  }
  private:
    int m_Ants;
    char m_Color; 
    int m_Id;
};
#endif // ANTHILL_H