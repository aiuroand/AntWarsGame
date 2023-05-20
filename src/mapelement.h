#ifndef MAP_ELEM
#define MAP_ELEM

class CCoords
{
  public:
    int m_X;
    int m_Y;
};

class CMapElem
{
  public:
      CMapElem( char owner,
                CCoords coord )
     : m_Owner ( owner ),
       m_Coords ( coord )
    {};
      ~CMapElem( void )
    {};
    virtual void print ( void ) = 0;

  protected: 
    char m_Owner;
    CCoords m_Coords;
};

#endif // MAP_ELEM