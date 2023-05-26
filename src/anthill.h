#ifndef ANTHILL_H
#define ANTHILL_H
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
  int getColor( void );
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
  private:
    int m_Ants;
    char m_Color; 
    int m_Id;
};
#endif // ANTHILL_H