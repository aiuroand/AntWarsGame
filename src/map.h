#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <chrono>
#include <thread>

#include "mapelement.h"
#include "screen.h"
#include "coords.h"
#include "wall.h"
#include "void.h"
#include "anthill.h"
#include "road.h"


class CMap
{
  public:
      CMap( std::string mapDir,
            CScreen * scr )
    : m_Height ( 0 ),
      m_Width ( 0 ),
      m_Screen ( scr )
    {    
      readMap ( mapDir );
    }
    int getAntHill ( CCoords coords );
    void print ( void );
    void add ( int id, int amount );
    char getColorOfId ( int id );
    void setColorOfId ( int id, char color );
    int getAntsOfId ( int id );
    int getAttackOfId ( int id );
    void setAntsOfId ( int id, int amount );
    void createAnts ( void );
    void attack ( const int from, const int to );
    char checkWinner ( void );
    int getStrongest ( char c );
    int getWeakest ( char c );
    int countHills ( char c );
    void createRoad( int from, int to, std::vector<std::vector< std::pair <char, bool> > > & map );
    CCoords getCoordsOfId ( int id );

    std::set < char > m_Players;

  private:
    void readMap ( std::string & mapDir );
    int m_Height;
    int m_Width;
    std::list< CMapElem * > m_ElementList;
    std::list< CAntHill * > m_AntHill;
    std::list< CRoad > m_Roads;
    CScreen * m_Screen;
};
#endif //MAP_H