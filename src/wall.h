#ifndef WALL_H
#define WALL_H
#include "mapelement.h"
#include "coords.h"
#include "screen.h"


class CWall : public CMapElem
{
  public:
    CWall ( CCoords coord )
   : CMapElem ( 'n', coord )
   {}
   void print ( CScreen * scr ) override
   {
     scr -> screenPrint ( m_Coords, "#" );
   }
};

#endif // WALL_H
