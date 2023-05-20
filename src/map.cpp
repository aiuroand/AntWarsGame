#include "map.h"

void CMap::readMap ( std::string mapDir )
{
  std::ifstream ifs ( mapDir, std::ios::in );
  int h, w;
  char c;
  
  std::cin>>h>>w;
  m_Height = h;
  m_Width = w;
  
  std::vector<std::vector<char>> map;

  for ( int i = 0; i < h; ++i )
  {
    for ( int j = 0; i < w; ++j )
    {
      ifs . get( c );
      map [i][j] = c;
    }
    ifs . get( c );
  }

  ifs . close();
  
}