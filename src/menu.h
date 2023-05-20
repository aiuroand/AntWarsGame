#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "screen.h"

class CMenu
{
  public:
      CMenu ( void )
     : m_Elements ( { "New Game", "Saved Games", "Rules", "Exit" } )
    {
      
    }
    void loop ( void );
  private:
    CScreen m_Screen;
    std::string m_Maps;
    std::string m_Saves;
    const std::vector < std::string > m_Elements;
};


#endif