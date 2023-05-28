#ifndef MAXANTS_H
#define MAXANTS_H
#include "talent.h"

/*! Child class of CTalent that represents maxants talent.
 */
class CMaxAnts: public CTalent
{
  public:
    /*! Constructor that firtsly constructs parent class CTalent.
     *  @param name        - name of the talent.
     *  @param description - description of the talent.
     *  @param chance      - chance to increase.
     */
    CMaxAnts ( std::string name,
               std::string description,
               int chance )
    : CTalent ( name, description ),
      m_Chance ( chance )
    {}

    /*! Default destructor 
     */
    ~CMaxAnts ( void ) = default;
        
    /*! Activates talent's bonus.
     *  With m_Chance / 10 chance maximizes amount of ants in random anthill of talent owner.
     *  @param c   - color of player, who should get bonus.
     *  @param map - game's map
     */
    inline void activate ( char c, CMap & map ) override
    {
      if ( rand() % 10 <= m_Chance )
        map . randomMax ( c );
    }

  private:

    int m_Chance;
};
#endif // MAXANTS_H