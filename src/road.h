#ifndef ROAD_H
#define ROAD_H

#define GREEN 1
#define WHITE 2
#define RED 3
#define MAGENTA 4

#include "mapelement.h"
#include "screen.h"
#include <vector>
#include "coords.h"

/*! Class that represents a road between two anthills
 */
class CRoad
{
  public:
    /*! Constructor
     *  @param first  - id of first anthill
     *  @param second - id of second anthill
     */
    CRoad( int first,
           int second )
    : m_First ( first ),
      m_Second ( second ),
      m_FirstUsed ( false ),
      m_SecondUsed ( false )
    {};

    /*! Default destructor 
     */
    ~CRoad ( void ) = default;

    /*! Method that is used to print road between two anthills 
     *  including all ans that are currently on the road
     *  @param scr - screen where a road shuld be printed
     */
    inline  void print ( CScreen * scr ) const 
    {
      for ( size_t i = 0; i < m_Vec . size(); ++i )
      {
        if ( m_VecAnts[i] . second == 'n' )
          mvwprintw ( scr -> m_Window, m_Vec[i] . m_Y, m_Vec[i] . m_X, "+" );
        else if ( m_VecAnts[i] . second != 'n' )
        {
          int c;
          if (      m_VecAnts[i] . second == 'g' )
            c = GREEN;
          else if ( m_VecAnts[i] . second == 'r' )
            c = RED;
          else if ( m_VecAnts[i] . second == 'm' )
            c = MAGENTA;

          wattron ( scr -> m_Window, COLOR_PAIR ( c ) );
          mvwprintw ( scr -> m_Window, m_Vec[i] . m_Y, m_Vec[i] . m_X, "%d", m_VecAnts[i] . first );
          wattroff ( scr -> m_Window, COLOR_PAIR ( c ) );
        }
      }
    }

    /*! Clears the road from any ants
     */
    inline void clearRoad ( void ) 
    {
      for ( size_t i = 0; i < m_VecAnts . size(); ++i )
        m_VecAnts[i] = std::make_pair ( 0, 'n' );
      m_FirstUsed = false;
      m_SecondUsed = false;
    }

    std::vector < CCoords > m_Vec;
    //! std::vector that represents if there are ants on these coordinates and their colors, ( 0, 'n') by default
    std::vector < std::pair < int, char > > m_VecAnts;
    //! Id of first anthill
    int m_First;
    //! Id of second anthill
    int m_Second;
    //! Boolean value that shows if the road will be used by first anthill
    bool m_FirstUsed;
    //! Boolean value that shows if the road will be used by second anthill
    bool m_SecondUsed;
};

#endif // ROAD_H