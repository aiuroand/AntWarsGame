#ifndef MOREMOVE_H
#define MOREMOVE_H
#include "talent.h"

class CMoreMove : public CTalent
{
  public:
    CMoreMove( std::string name,
               std::string description,
               int amount )
    : CTalent ( name, description ),
      m_Amount ( amount )
    {}
    void activate ( char c, CMap & map ) override
    {
      map . addMoveToColor( c, m_Amount );
    }
  private:
    int m_Amount;
};
#endif // MOREMOVE_H