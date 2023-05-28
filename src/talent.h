#ifndef TALENT_H
#define TALENT_H
#include <iostream>
#include "map.h"

class CTalent
{
  public:
    CTalent ( std::string name,
              std::string description )
    : m_Name ( name ),
      m_Description ( description )
    {}
    virtual ~CTalent ( void ) = default;
    std::string getName ( void ) const
    {
      return m_Name;
    }
    std::string getDescription ( void ) const
    {
      return m_Description;
    }
    virtual void activate( char c, CMap & map ) = 0;
  protected:
    std::string m_Name;
    std::string m_Description;
};

#endif // TALENT_H