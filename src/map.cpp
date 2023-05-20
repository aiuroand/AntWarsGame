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

  std::vector<std::vector<char>> map( m_Height, std::vector<char>( m_Width ) );

  for ( int i = 0; i < m_Height; ++i )
  {
    for ( int j = 0; j < m_Width; ++j )
    {
      ifs . get( c );
      map [i][j] = c;
    }
    ifs . get( c );
  }

  ifs . close();
}

void CMap::print ( void )
{
  
}