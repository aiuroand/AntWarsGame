#include "mapelement.h"
#include "screen.h"
#include "coords.h"

class CAntHill: public CMapElem
{
  public:
      CAntHill ( CCoords coord,
                 char owner,
                 char color,
                 int ants )
     : CMapElem ( owner, coord ),
       m_Ants ( ants ),
       m_Color ( color )
    {}
  void print ( CScreen * scr ) override;
  int getColor( void );
  private:
    int m_Ants;
    char m_Color; 
};