#ifndef VOID_H
#define VOID_H
#include "mapelement.h"
#include "coords.h"
#include "screen.h"

class CVoid : public CMapElem
{
  public:
      CVoid ( CCoords coord )
     : CMapElem ( 'n', coord )
    {}
    void print ( CScreen * scr ) override
    {
      scr -> screenPrint ( m_Coords, " " );
    }
};

#endif // VOID_H