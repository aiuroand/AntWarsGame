#ifndef MOREANTS_H
#define MOREANTS_H
#include "talent.h"

/*! Child class of CTalent that represents moreants talent.
 */
class CMoreAnts : public CTalent
{
  public:
    /*! Constructor that firtsly constructs parent class CTalent.
     *  @param name        - name of the talent.
     *  @param description - description of the talent.
     *  @param amount      - amount of ants to add to attack.
     */
    CMoreAnts ( std::string name,
                std::string description,
                int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}

    /*! Activates talent's bonus.
     *  Increases 'ants per attack' value for all anthills of given color by m_Amount.
     *  @param c   - color of player, whose anthills should be buffed.
     *  @param map - game's map
     */
    inline void activate ( char c, CMap & map ) override
    {
      map . addAntsAttackToColor( c, m_Amount );
    }

  private:

    int m_Amount;
};
#endif // MOREANTS_H