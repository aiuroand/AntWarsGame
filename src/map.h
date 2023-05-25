#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "mapelement.h"
#include "screen.h"
#include "coords.h"
#include "wall.h"
#include "void.h"
#include "anthill.h"

class CMap
{
  public:
      CMap( std::string mapDir,
            CScreen * scr )
    : m_Height ( 0 ),
      m_Width ( 0 ),
      m_Screen ( scr )
    {
      readMap ( mapDir );
    }
    void print ( void );
  private:
    void readMap ( std::string & mapDir );
    int m_Height;
    int m_Width;
    std::list< CMapElem * > m_ElementList;
    CScreen * m_Screen;

};



#endif //MAP_H