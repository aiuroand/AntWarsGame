#ifndef TALENT_H
#define TALENT_H

#include <iostream>
#include "map.h"

/*! Abstract parent class that represent talents.
 */
class CTalent
{
  public:
    /*! Constructior.
     *  @param name        - name of talent.
     *  @param description - description of talent.
     */
    CTalent ( std::string name,
              std::string description )
    : m_Name ( name ),
      m_Description ( description )
    {}

    /*! Virtual destructor. 
     */
    virtual ~CTalent ( void ) = default;
    
    /*! Gets talent's name. 
     *  @return talent's name. 
     */
    inline std::string getName ( void ) const
    {
      return m_Name;
    }

    /*! Gets talent's description.
     *  @return talent's description.
     */
    inline std::string getDescription ( void ) const
    {
      return m_Description;
    }

    /*! Abstract method that allowes to use talent's bonus.
     *  @param c   - color of player, whose anthills should be buffed.
     *  @param map - game's map
     */
    virtual void activate( char c, CMap & map ) = 0;

  protected:
  
    std::string m_Name;
    std::string m_Description;
};

#endif // TALENT_H