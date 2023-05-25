#ifndef MAP_ELEM
#define MAP_ELEM
#include "coords.h"
#include "screen.h"

class CMapElem
{
  public:
      CMapElem( char owner,
                CCoords coord )
     : m_Owner ( owner ),
       m_Coords ( coord )
    {};
    virtual ~CMapElem( void )
    {};
    virtual void print ( CScreen * scr ) = 0;

  protected: 
    char m_Owner;
    CCoords m_Coords;
};

#endif // MAP_ELEM