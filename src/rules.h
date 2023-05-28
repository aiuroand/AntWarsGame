#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <fstream>
#include <string>
#include "screen.h"
#include "ncurses.h"
#include "exceptions.h"

class CRules
{
  public:
    /*! Constructing rules
     *  @param screen - represents pointer to main program screen
     *  @param dir    - represents file with game rules
     */
    CRules ( CScreen * screen,
             std::string dir )
    : m_Screen ( screen ),
      m_Dir ( dir )
    {}

    /*! Main loop that prints out the rules to the screen
     */
    void loop ( void );

  private:
    CScreen * m_Screen;
    std::string m_Dir;
};
#endif // RULES_H