#include "map.h"

void CMap::readMap ( std::string & mapDir )
{
  std::ifstream ifs ( mapDir, std::ios::in );
  char c;
  // Reading height and width of map that are given in format 'hh ww\n' on the first line.
  // Max width and max height = 99;
  ifs . get ( c );
  m_Height += ( ( ( int ) c ) - 48 ) * 10;
  ifs . get ( c );
  m_Height += ( ( ( int ) c ) - 48 );
  ifs . get ( c );
  ifs . get ( c );
  m_Width += ( ( ( int ) c ) - 48 ) * 10;
  ifs . get ( c );
  m_Width += ( ( ( int ) c ) - 48 );
  ifs . get ( c );

  std::vector<std::vector< std::pair <char, bool> > > map( m_Height, std::vector< std::pair <char, bool> >( m_Width ) );

  for ( int i = 0; i < m_Height; ++i )
  {
    for ( int j = 0; j < m_Width; ++j )
    {
      ifs . get( c );
      map [i][j] . first = c;
      map [i][j] . second = false;
    }
    ifs . get( c );
  }
  ifs . close();

  for ( int i = 0; i < m_Height; ++i )
    for ( int j = 0; j < m_Width; ++j )
      if ( !map[i][j] . second )
        switch ( map[i][j] . first )
        {
          case '#':
            m_ElementList . push_back ( new CWall( CCoords ( j, i ) ) );
            map[i][j] . second = true;
            break;
          case ' ':
            m_ElementList . push_back ( new CVoid( CCoords ( j, i ) ) );
            map[i][j] . second = true;
            break;
          case '*':
            for ( int k = 0; k < 6; k++ )
              for ( int k1 = 0; k1 < 3; k1++ )
              map[i + k1][j + k] . second = true;
            m_ElementList . push_back ( new CAntHill( CCoords ( j, i ),
                                                      map[i+1][j+1] . first,
                                                      map[i+1][j+2] . first,
                                                      (int)(map[i+1][j+3] . first - 48) * 10 + (int)(map[i+1][j+4] . first - 48) ) );

            break;
          default:
            break;
        }
}  
  
void CMap::print ( void )
{
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  for ( const auto & it : m_ElementList )
    it -> print ( m_Screen );
  m_Screen -> screenRefresh();
}