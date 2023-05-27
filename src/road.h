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
      for ( size_t i = 0; i < m_Vec . size(); ++i )
      {
        if ( m_VecAnts[i] . second == 'n' )
          mvwprintw ( scr -> m_Window, m_Vec[i] . m_Y, m_Vec[i] . m_X, "+" );
        else if ( m_VecAnts[i] . second != 'n' )
        {
          int c;
          if (      m_VecAnts[i] . second == 'g' )
            c = 1;
          else if ( m_VecAnts[i] . second == 'r' )
            c = 3;

          wattron ( scr -> m_Window, COLOR_PAIR ( c ) );
          mvwprintw ( scr -> m_Window, m_Vec[i] . m_Y, m_Vec[i] . m_X, "%d", m_VecAnts[i] . first );
          wattroff ( scr -> m_Window, COLOR_PAIR ( c ) );
        }
      }
    }
    void clearRoad ( void ) 
    {
      for ( size_t i = 0; i < m_VecAnts . size(); ++i )
        m_VecAnts[i] = std::make_pair ( 0, 'n' );
      m_FirstUsed = false;
      m_SecondUsed = false;
    }
    std::vector < CCoords > m_Vec;
    std::vector < std::pair < int, char > > m_VecAnts;
    int m_First;
    int m_Second;
    bool m_FirstUsed;
    bool m_SecondUsed;
    bool m_Exists;

};

#endif // ROAD_H