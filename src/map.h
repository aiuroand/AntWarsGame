#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CMap
{
  public:
      CMap( std::string mapDir )
    : m_Height ( 0 ),
      m_Width ( 0 )
    {
      readMap ( mapDir );
    }

  private:
    void readMap ( std::string & mapDir );
    int m_Height;
    int m_Width;
};



#endif //MAP_H