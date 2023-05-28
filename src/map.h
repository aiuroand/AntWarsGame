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
      m_Round ( 1 ),
      m_Screen ( scr )
    {    
      readMap ( mapDir );
    }
    ~CMap ( void )
    {
      for ( const auto & it : m_ElementList )
        delete it;
      for ( const auto & it : m_AntHill )
        delete it;
    }
    int getAntHill ( CCoords coords );
    void print ( void );
    void add ( int id, int amount );
    char getColorOfId ( int id );
    void setColorOfId ( int id, char color );
    int getAntsOfId ( int id );
    int getAttackOfId ( int id );
    int getArmorOfId ( int id );
    CAntHill * getAntHillOfId ( int id );
    void setAntsOfId ( int id, int amount );
    void createAnts ( void );
    void fillRoad ( const int from, const int to );
    void clearRoads ( void );
    void attack ( void );
    char checkWinner ( void );
    int getStrongest ( char c );
    int getWeakest ( char c );
    int countHills ( char c );
    void deactivateAll ( void );
    void addAntsAttackToColor ( char c, int amount );
    void addArmorToColor ( char c, int amount );
    void addMoveToColor ( char c, int amount );
    void addMaxToColor ( char c, int amount );
    void randomMax ( char c );
    void randomConquer ( char c );
    void save (std::vector<std::vector< std::pair <char, bool> > > & map );
    int getHeight( void ) const
    {
      return m_Height;
    }
    int getWidth( void ) const
    {
      return m_Width;
    }
    int getRound( void ) const
    {
      return m_Round;
    }
    void setRound( int i )
    {
      m_Round = i;
    }
    void createRoad( int from, int to, std::vector<std::vector< std::pair <char, bool> > > & map );
    CCoords getCoordsOfId ( int id );

    std::set < std::pair < char, unsigned int > > m_Players;

  private:
    void readMap ( std::string & mapDir );
    int m_Height;
    int m_Width;
    int m_Round;
    std::list< CMapElem * > m_ElementList;
    std::list< CAntHill * > m_AntHill;
    std::list< CRoad > m_Roads;
    CScreen * m_Screen;
};
#endif //MAP_H