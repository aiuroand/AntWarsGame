#ifndef ROAD_H
#define ROAD_H

#include "mapelement.h"
#include "screen.h"
#include <vector>
#include "coords.h"

class CRoad
{
  public:
    CRoad( int first,
           int second )
    : m_First ( first ),
      m_Second ( second ),
      m_FirstUsed ( false ),
      m_SecondUsed ( false )
    {};
    void print ( CScreen * scr ) const 
    {
      for ( const auto & it : m_Vec )
        mvwprintw ( scr -> m_Window, it . m_Y, it . m_X, "%c", '+' );
    }
    std::vector < CCoords > m_Vec;
    int m_First;
    int m_Second;
    bool m_FirstUsed;
    bool m_SecondUsed;
    bool m_Exists;

};

#endif // ROAD_H