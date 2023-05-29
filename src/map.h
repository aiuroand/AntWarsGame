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
#include <cstring>

#include "mapelement.h"
#include "screen.h"
#include "coords.h"
#include "wall.h"
#include "void.h"
#include "anthill.h"
#include "road.h"
#include "exceptions.h"


class CMap
{
  public:

    /*! Constructing object taht represents game map
     *  @param mapDir - filename of map that should be loaded
     *  @param scr    - pointer to main screen 
     */
    CMap( std::string mapDir,
          CScreen * scr )
    : m_Height ( 0 ),
      m_Width ( 0 ),
      m_Round ( 1 ),
      m_Screen ( scr )
    { 
      readMap ( mapDir );
    }

    /*! Deleting all allocated resourses
     */
    ~CMap ( void )
    {
      for ( const auto & it : m_ElementList )
        delete it;
      for ( const auto & it : m_AntHill )
        delete it;
    }

    /*! Getting id of anthill that is standing on the coords
     *  @param coords - coords to check
     *  @return id of anthill, -1 if wan not found
     */
    int getAntHill ( CCoords coords ) const;

    /*! Returns id of an anthill of given color that contains maximum amount of ants on the map
     *  @param c - color of owner
     *  @return id of the strongest anthill that has given color, -1 if was not found
     */
    int getStrongest ( char c ) const;

    /*! Returns id of an anthill that has not given color and contains minimum amount of ants on the map 
     *  @param c - color of owner
     *  @return id of the weakest anthill that has given color, -1 if was not found
     */
    int getWeakest ( char c ) const;
    
    /*! Counts amount of anthills of given owner
     *  @param c - color of owner
     *  @return amount of anthills of the onwer
     */
    int countHills ( char c ) const;

    /*! Gets amount of ants in the anthill
     *  @param id - id of anthill
     *  @return amount of anthills, -1 if such anthill does not exist
     */
    int getAntsOfId ( int id ) const;

    /*! Gets amount of ants per attack of the anthill
     *  @param id - id of anthill
     *  @return amount of ants per attack of anthills, -1 if such anthill does not exist
     */
    int getAttackOfId ( int id ) const;

    /*! Gets amount of armor of the anthill
     *  @param id - id of anthill
     *  @return amount of armor, -1 if such anthill does not exist
     */
    int getArmorOfId ( int id ) const;

    /*! Gets color of the anthill
     *  @param id - id of anthill
     *  @return color of anthill, 'n' if such anthill does not exist
     */
    char getColorOfId ( int id ) const;

    /*! Checks if there are more than 1 color on the map
     *  @return color of left player, 'n' if there are more than 1 player, or if there are neutral anhills
     */
    char checkWinner ( void ) const;

    /*! Gets pointer to anthill of given id
     *  @param id - id of anthill
     *  @return pointer to anthill
     */
    CAntHill * getAntHillOfId ( int id ) const;
    
    /*! Gets coords of anthill of given id
     *  @param id - id of anthill
     *  @return coords ( left top corner ) of anthill
     */
    CCoords getCoordsOfId ( int id ) const;

    /*! Changes color of given anthill
     *  @param id    - id of anthill
     *  @param color - color that should be set
     */
    void setColorOfId ( int id, char color );

    /*! Changes amount of ants in given anthill
     *  @param id     - id of anthill
     *  @param amount - amount to be set
     */
    void setAntsOfId ( int id, int amount );

    /*! If anthill is not neutral increases amount of ants in anthill by constant
     *  that is declared in CAntHill
     */
    void createAnts ( void );

    /*! Prepares a road for using in the next attack circle
     *  @param from - id of attacker
     *  @param to   - id 0f defender
     */
    void fillRoad ( const int from, const int to );
    
    /*! Resets all roads to defaul settings
     */
    void clearRoads ( void );

    /*! Helping function for attack function, that recieves id and returns it's
     *  color on char * format
     *  @param str - char[] where color should be printed, max 30, neutral for white anthills
     *  @param id  - id
     */
    void getCharColor ( char * str, int id ) const;
    
    /*! Implemenst logic of attack, animates and calculates them
     */
    void attack ( void );

    /*! Prints all CMapElement object on m_Screen
     */
    void print ( void ) const;
    
    /*! Adds ( or removes if amount < 0 ) ants to m_Ants in a given anthill
     *  @param id     - id of anthill
     *  @param amount - amount to be added
     */
    void add ( int id, int amount );

    /*! Resets all anthills to defaul settings
     */
    void deactivateAll ( void );

    /*! Adds ( or removes if amount < 0 ) ants per attack value to anthills of given color
     *  @param c      - color of anthills
     *  @param amount - amount to be added
     */
    void addAntsAttackToColor ( char c, int amount );

    /*! Adds ( or removes if amount < 0 ) armor value to anthills of given color
     *  @param c      - color of anthills
     *  @param amount - amount to be added
     */
    void addArmorToColor ( char c, int amount );

    /*! Adds ( or removes if amount < 0 ) ants per move value to anthills of given color
     *  @param c      - color of anthills
     *  @param amount - amount to be added
     */
    void addMoveToColor ( char c, int amount );
    
    /*! Adds ( or removes if amount < 0 ) max ants value to anthills of given color
     *  @param c      - color of anthills
     *  @param amount - amount to be added
     */
    void addMaxToColor ( char c, int amount );
    
    /*! Increases amount of ants in a random anthill of given color to maximum possible amount
     *  @param c - color of anthills
     */
    void randomMax ( char c );

    /*! Changes color of owner of random neutral anthill to given color
     *  @param c - color of new owner
     */
    void randomConquer ( char c );

    /*! Gets m_Height of the map
     */
    inline int getHeight( void ) const
    {
      return m_Height;
    }

    /*! Gets m_Width of the map 
     */
    inline int getWidth( void ) const
    {
      return m_Width;
    }

    /*! Gets m_Round value 
     */
    inline int getRound( void ) const
    {
      return m_Round;
    }

    /*! Sets m_Round value 
     *  @param i - value to be set
     */
    inline void setRound( int i )
    {
      m_Round = i;
    }

    /*! Creating a road of coords from 1st anthill to second using BFS
     *  @param from - value to be set
     *  @param to - value to be set
     *  @param map - 2d map of std::pairs, where: first is a symbol on this position
     *                                            second is a bool value, that represents if this position was visited or not
     *  @throw CRoadDoesNotExist - if it is impossible to find a road between anthills
     */
    void createRoad( int from, int to, std::vector<std::vector< std::pair <char, bool> > > & map );

    /*! Fills 2d array by map's objects to save it further
     *  @param map - 2d map of std::pairs where: first is a symbol on this position
     *                                           second is a bool value, that represents if this position was visited or not
     */
    void save (std::vector < std::vector < std::pair <char, bool> > > & map );

    std::set < std::pair < char, unsigned int > > m_Players;

  private:
    /*! Reading map from file
     *  @param mapDir - name of file
     *  @throw CFileReadingError - if something wrong happend during file reading file
     *  @throw CRoadDoesNotExist - if it is impossible to find a road between some 2 anthills
     *  @throw CDamagedFile      - if a file is somehow damaged and unreadable
     */
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