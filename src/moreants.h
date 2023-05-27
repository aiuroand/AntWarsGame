#ifndef MOREANTS_H
#define MOREANTS_H
#include "talent.h"

class CMoreAnts : public CTalent
{
  public:
    CMoreAnts ( std::string name,
                std::string description,
                int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}
    void activate ( char c, CMap & map ) override
    {
      map . addAntsAttackToColor( c, m_Amount );
    }
  private:
    int m_Amount;
};
#endif // MOREANTS_H