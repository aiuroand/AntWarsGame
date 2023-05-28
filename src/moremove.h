#ifndef MOREMOVE_H
#define MOREMOVE_H
#include "talent.h"

/*! Child class of CTalent that represents moremove talent.
 */
class CMoreMove : public CTalent
{
  public:
    /*! Constructor that firtsly constructs parent class CTalent.
     *  @param name        - name of the talent.
     *  @param description - description of the talent.
     *  @param amount      - amount of ants to add to spawnrate.
     */
    CMoreMove( std::string name,
               std::string description,
               int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}

    /*! Default destructor 
     */
    ~CMoreMove ( void ) = default;
    
    /*! Activates talent's bonus.
     *  Increases spawnrate ( m_Move ) value for all anthills of given color by m_Amount.
     *  @param c   - color of player, whose anthills should be buffed.
     *  @param map - game's map
     */
    inline void activate ( char c, CMap & map ) override
    {
      map . addMoveToColor( c, m_Amount );
    } 

  private: 

    int m_Amount;
};
#endif // MOREMOVE_H