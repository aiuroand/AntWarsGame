#ifndef MAP_ELEM
#define MAP_ELEM
#include "coords.h"
#include "screen.h"

class CMapElem
{
  public:
    CMapElem( char c,
              CCoords coord )
    : m_Color ( c ),          
      m_Coords ( coord )
    {};
    virtual ~CMapElem( void ) = default;
    virtual void print ( CScreen * scr ) = 0;

  protected: 
    char m_Color;
    CCoords m_Coords;
};

#endif // MAP_ELEM