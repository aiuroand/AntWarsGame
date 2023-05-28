#ifndef ANTHILL_H
#define ANTHILL_H
#define ANTS_MAX 10
#define ANTS_MOVE 1
#define ANTS_ATTACK 3
#define ANTS_ARMOR 0

#define GREEN 1
#define WHITE 2
#define RED 3
#define YELLOW 4

#include "mapelement.h"
#include "screen.h"
#include "coords.h"

class CAntHill: public CMapElem
{
  public:
    /*! Constructor
     *  @param coords of left top corner of anthill
     *  @param color color of owner of anthill 
     *  @param ants amount of ants in anthill when created
     *  @param id id of anthill
     */
    CAntHill ( CCoords coords,
               char color,
               int ants,
               int id )
    : CMapElem ( color, coords ),
      m_Ants ( ants ),
      m_Id ( id ),
      m_Move ( ANTS_MOVE ),
      m_Attack ( ANTS_ATTACK ),
      m_Armor ( ANTS_ARMOR ),
      m_Max ( ANTS_MAX )
    {}
  void print ( CScreen * scr ) override;
  bool isInside ( CCoords coord ) const
  {
    return coord . m_X >= m_Coords . m_X 
        && coord . m_Y >= m_Coords . m_Y
        && coord . m_X <= m_Coords . m_X + 4
        && coord . m_Y <= m_Coords . m_Y + 2;
  }
  char get ( void ) const  override
  {
    return '*';
  }
  int getId ( void ) const 
  {
    return m_Id;
  }
  int getAnts ( void ) const 
  {
    return m_Ants;
  }
  char getColor( void ) const
  {
    return m_Color;
  }
  int getAttack( void ) const
  {
    return m_Attack <= m_Ants ? m_Attack : m_Ants;
  }
  int getArmor ( void ) const
  {
    return m_Armor;
  }
  void setColor( char c )
  {
    m_Color = c;
  }
  void setAnts ( int amount )
  {
    m_Ants = amount;
  }
  void addAttack ( int amount )
  {
    m_Attack += amount;
  }
  void addArmor ( int amount )
  {
    m_Armor += amount;
  }
  void addMax ( int amount )
  {
    m_Max += amount;
  }
  void addMove ( int amount )
  {
    m_Move += amount;
  }
  void add ( int amount )
  {
    if ( m_Ants + amount < m_Max ) 
      m_Ants += amount;
    else 
      m_Ants = m_Max;
    if ( m_Ants < 0 )
      m_Ants += m_Armor;
  }
  void createAnts ( void )
  {
    m_Ants += m_Move;
    if ( m_Ants > m_Max )
      m_Ants = m_Max;
  }
  void clearAntHill( void )
  {
    m_Move = ANTS_MOVE;
    m_Attack = ANTS_ATTACK;
    m_Armor = ANTS_ARMOR;
    m_Max = ANTS_MAX;
  }
  private:
    int m_Ants;
    int m_Id;
    int m_Move;
    int m_Attack;
    int m_Armor;
    int m_Max;
};
#endif // ANTHILL_H