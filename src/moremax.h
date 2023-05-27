#ifndef MOREMAX_H
#define MOREMAX_H
#include "talent.h"

class CMoreMax : public CTalent
{
  public:
    CMoreMax ( std::string name,
               std::string description,
               int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}
    void activate ( char c, CMap & map ) override
    {
      map . addMaxToColor( c, m_Amount );
    }
  private:
    int m_Amount;
};
#endif // MOREMAX_H