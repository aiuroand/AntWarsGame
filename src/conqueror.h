#ifndef CONQUEROR_H
#define CONQUEROR_H
#include "talent.h"

class CConqueror: public CTalent
{
  public:
    CConqueror ( std::string name,
                 std::string description,
                 int chance )
    : CTalent ( name, description ),
      m_Chance ( chance )
    {}
    void activate ( char c, CMap & map ) override
    {
      if ( rand() % 10 <= m_Chance )
        map . randomConquer ( c );
    }
  private:
    int m_Chance;
};
#endif // CONQUEROR_H