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
#include <ncurses.h>
#include "screen.h"
#include "coords.h"

/*! Child class of CMapElem that represents anthill.
 */
class CAntHill: public CMapElem
{
  public:
    /*! Constructor that firtsly constructs parent class CMapElem.
     *  @param coords - coords of left top corner of anthill.
     *  @param color  - owner's color.
     *  @param ants   - amount of ants in anthill when created.
     *  @param id     - id of anthill.
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

    /*! Destructor 
     */
    ~CAntHill ( void ) = default;

    /*! Overrided method that is used to draw anthill on the screen.
     *  @param sct - screen, represented by CScreen class, where anthill should be drawn on.
     */
    void print ( CScreen * scr ) const override;

    /*! Overrided method that is used to get borders in char format.
     *  @return char value that represents anthill's borders.
     */
    char get ( void ) const  override
    {
      return '*';
    }

    /*! Checkes if the coordinates are inside of anthill of not.
     *  @param coords - coordinates to check. 
     *  @return true if inside, false if outside.
     */
    inline bool isInside ( CCoords coords ) const
    {
      return coords . m_X >= m_Coords . m_X 
          && coords . m_Y >= m_Coords . m_Y
          && coords . m_X <= m_Coords . m_X + 4
          && coords . m_Y <= m_Coords . m_Y + 2;
    }

    /*! Gets anthill's id.
     *  @return anthill's id.
     */
    inline int getId ( void ) const 
    {
      return m_Id;
    }

    /*! Gets nubmer of ants in anthill.
     *  @return number of ants.
     */
    inline int getAnts ( void ) const 
    {
      return m_Ants;
    }
    
    /*! Gets color of anthill.
     *  @return color of anthill.
     */
    inline char getColor( void ) const
    {
      return m_Color;
    }
    
    /*! Gets amount of ants avilable for attack.
     *  @return max ( m_Attack, m_Ants ).
     */
    inline int getAttack( void ) const
    {
      return m_Attack <= m_Ants ? m_Attack : m_Ants;
    }
    
    /*! Gets armor value of anthill.
     *  @return armor value.
     */
    inline int getArmor ( void ) const
    {
      return m_Armor;
    }

    /*! Changes color of anthill.
     *  @param c - new color.
     */
    inline void setColor( char c )
    {
      m_Color = c;
    }

    /*! Changes amount of ants inside of anthill.
     *  @param amount - new amount.
     */
    inline void setAnts ( int amount )
    {
      m_Ants = amount;
    }
  
    /*! Increases 'ants per attack' value for current anthill.
     *  @param amount - increase number.
     */
    inline void addAttack ( int amount )
    {
      m_Attack += amount;
    }

    /*! Increases  armor value for current anthill.
     *  @param amount - increase number.
     */
    inline void addArmor ( int amount )
    {
      m_Armor += amount;
    }

    /*! Increases upper boundary for max amount of ants in current anthill.
     *  @param amount - increase number.
     */
    inline void addMax ( int amount )
    {
      m_Max += amount;
    }
    
    /*! Increases amount of ants per attack in current anthill.
     *  @param amount - increase number.
     */
    inline void addMove ( int amount )
    {
      m_Move += amount;
    }

    /*! Increases (decreases if amount < 0 ) amount of ants in current anthill.
     *  If after increasing amount of ants > amount of ant allowed: amount of ants = amount of ant allowed.
     *  If after decreasing amount of ants < 0 armor tries to compensate losses.
     *  @param amount - increase ( decrease ) number.
     */
    inline void add ( int amount )
    {
      if ( m_Ants + amount < m_Max ) 
        m_Ants += amount;
      else 
        m_Ants = m_Max;
      if ( m_Ants < 0 )
        m_Ants += m_Armor;
    }

    /*! Creates new ants in current anthill.
     *  If after increasing amount of ants > amount of ant allowed: amount of ants = amount of ant allowed.
     */
    inline void createAnts ( void )
    {
      m_Ants += m_Move;
      if ( m_Ants > m_Max )
        m_Ants = m_Max;
    }
    
    /*! Restores anthill's settings to default.
     *  Default settings are represented by ANTS_MOVE, ANTS_ATTACK,
     *  ANTS_ARMOR and ANTS_MAX constants.
     */
    inline void clearAntHill( void )
    {
      m_Move = ANTS_MOVE;
      m_Attack = ANTS_ATTACK;
      m_Armor = ANTS_ARMOR;
      m_Max = ANTS_MAX;
    }

  private:
    //! Number of ants in anthill.
    int m_Ants;
    //! Id of anthill.
    int m_Id;
    //! Number of ants anthill craetes in 1 move. By default ANTS_MOVE.
    int m_Move;
    //! Number of ants anthill sends per 1 attack. By default ANTS_ATTACK.
    int m_Attack;
    //! Number of armor anthill has. By default ANTS_ARMOR.
    int m_Armor;
    //! Max ants amount allowed in anthill. By default ANTS_MAX.
    int m_Max;
};
#endif // ANTHILL_H