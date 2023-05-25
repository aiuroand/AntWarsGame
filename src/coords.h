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
    int m_X;
    int m_Y;
};
#endif // COORDS_H
