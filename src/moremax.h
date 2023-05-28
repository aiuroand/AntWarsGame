#ifndef MOREMAX_H
#define MOREMAX_H
#include "talent.h"

/*! Child class of CTalent that represents moremax talent.
 */
class CMoreMax : public CTalent
{
  public:
    /*! Constructor that firtsly constructs parent class CTalent.
     *  @param name        - name of the talent.
     *  @param description - description of the talent.
     *  @param amount      - number that upper boundary of ants should be increased by.
     */
    CMoreMax ( std::string name,
               std::string description,
               int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}

    /*! Activates talent's bonus.
     *  Increases upper boundary value ( m_Max ) for all anthills of given color by m_Amount.
     *  @param c   - color of player, whose anthills should be buffed.
     *  @param map - game's map
     */
    inline void activate ( char c, CMap & map ) override
    {
      map . addMaxToColor( c, m_Amount );
    }

  private:

    int m_Amount;
};
#endif // MOREMAX_H