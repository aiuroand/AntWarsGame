#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <fstream>
#include <string>
#include "screen.h"
#include "ncurses.h"
#include "status.h"

class CRules
{
  public:
      CRules ( CScreen * screen,
               EStatus & status,
               std::string dir )
     : m_Screen ( screen ),
       m_Status ( status ),
       m_Dir ( dir )
    {}
    void loop ( void );
  private:
    CScreen * m_Screen;
    EStatus & m_Status;
    std::string m_Dir;
};

#endif // RULES_H