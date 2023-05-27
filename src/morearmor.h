#ifndef MOREARMOR_H
#define MOREARMOR_H
#include "talent.h"

class CMoreArmor : public CTalent
{
  public:
    CMoreArmor( std::string name,
                std::string description,
                int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}
    void activate ( char c, CMap & map ) override
    {
      map . addArmorToColor( c, m_Amount );
    }
  private:
    int m_Amount;
};
#endif // MOREARMOR_H