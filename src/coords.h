#ifndef COORDS_H
#define COORDS_H

/*! Class that is used to represent 2d coords
 */
class CCoords
{
  public:
    /*! Constructor
     *  @param - x coordinate
     *  @param - y coordinate
     */
      CCoords ( int x,
                int y )
    : m_X ( x ),
      m_Y ( y )
    {}

    /*! Operator ==
     *  @param - a CCoords object to compare with
     */
    inline bool operator== ( const CCoords & a ) const
    {
      return m_X == a . m_X && m_Y == a . m_Y;
    }
    
    /*! Operator !=
     *  @param - a CCoords object to compare with
     */
    inline bool operator!= ( const CCoords & a ) const
    {
      return !(*this == a );
    }

    /*! Operator <
     *  @param - a CCoords object to compare with
     */
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
