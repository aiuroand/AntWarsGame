#ifndef CONQUEROR_H
#define CONQUEROR_H

#include "talent.h"

/*! Child class of CTalent that represents conqueror talent.
 */
class CConqueror: public CTalent
{
  public:
    /*! Constructor that firtsly constructs parent class CTalent.
     *  @param name        - name of the talent.
     *  @param description - description of the talent.
     *  @param chance      - chance to conquer.
     */
    CConqueror ( std::string name,
                 std::string description,
                 int chance )
    : CTalent ( name, description ),
      m_Chance ( chance )
    {}

    /*! Default destructor 
     */
    ~CConqueror ( void ) = default;
    
    /*! Activates talent's bonus.
     *  With m_Chance / 10 chance conquers random neutral ant on the map.
     *  @param c   - color of player, whose should recieve neutral anthill.
     *  @param map - game's map
     */
    inline void activate ( char c, CMap & map ) override
    {
      if ( rand() % 10 <= m_Chance )
        map . randomConquer ( c );
    }

  private:

    int m_Chance;
};
#endif // CONQUEROR_H