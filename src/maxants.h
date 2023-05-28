#ifndef MAXANTS_H
#define MAXANTS_H
#include "talent.h"

class CMaxAnts: public CTalent
{
  public:
    CMaxAnts ( std::string name,
               std::string description,
               int chance )
    : CTalent ( name, description ),
      m_Chance ( chance )
    {}
    void activate ( char c, CMap & map ) override
    {
      if ( rand() % 10 <= m_Chance )
        map . randomMax ( c );
    }
  private:
    int m_Chance;
};
#endif // MAXANTS_H