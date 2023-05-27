#include "road.h"
void CRoad::attack ( void )
{
  CRoad road ( 0, 0 );
  for ( const auto & it : m_Roads )
    if (  ( ( it . m_First == from && it . m_Second == to )
         || ( it . m_First == to && it . m_Second == from ) ) ) 
      road = it;
  
  for ( size_t i = 0; i < road . m_VecAnts . size() - 1; ++i )
  {
    if ( road . m_FirstUsed )
    {
      road . m_VecAnts[ road . m_VecAnts . size() - 2 - i ] . first  = road . m_VecAnts[ road . m_VecAnts . size() - 1 - i ] . first;
      road . m_VecAnts[ road . m_VecAnts . size() - 2 - i ] . second = road . m_VecAnts[ road . m_VecAnts . size() - 1 - i ] . second;
      road . m_VecAnts[ road . m_VecAnts . size() - 1 - i ] . first = 0;
      road . m_VecAnts[ road . m_VecAnts . size() - 1 - i ] . second = 'n';
    }
    if ( road . m_SecondUsed )
    {
      road . m_VecAnts[ i + 1 ] . first  = road . m_VecAnts[ i ] . first;
      road . m_VecAnts[ i + 1 ] . second = road . m_VecAnts[ i ] . second;
      road . m_VecAnts[ i ] . first = 0;
      road . m_VecAnts[ i ] . second = 'n';
    }
    road . print( m_Screen );
    wrefresh ( m_Screen -> m_Window );
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  }
  print();
}