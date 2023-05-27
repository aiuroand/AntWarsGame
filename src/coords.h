#ifndef COORDS_H
#define COORDS_H
class CCoords
{
  public:

      CCoords ( int x,
                int y )
    : m_X ( x ),
      m_Y ( y )
    {}
    inline bool operator== ( const CCoords & a ) const
    {
      return m_X == a . m_X && m_Y == a . m_Y;
    }
    inline bool operator!= ( const CCoords & a ) const
    {
      return !(*this == a );
    }
    inline bool operator < ( const CCoords & a ) const 
    {
      if ( m_X == a . m_X )
        return m_Y < a . m_Y;
      return m_X < a . m_X;
    }
    int m_X;
    int m_Y;
};
#endif // COORDS_H
