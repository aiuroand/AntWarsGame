#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <filesystem>
#include <list>
#include <string>
#include <vector>
#include "screen.h"
#include "ncurses.h"
#include "status.h"

class CMenu
{
  public:
      CMenu ( CScreen * screen,
              EStatus & status,
              std::string maps,
              std::string saves )
     : m_HighlightMaps ( 0 ),
       m_Screen ( screen ),
       m_Status ( status ),
       m_Maps ( maps ), 
       m_Saves ( saves ), 
       m_Elements ( { "New Game", "Saved Games", "Rules", "Exit" } ),
       m_Highlight ( 0 )
    {
      
    }
    void loop ( void );
    void chooseNewMap ( void );
    
    int m_HighlightMaps;
  
  private:
    CScreen * m_Screen;
    EStatus & m_Status;
    std::string m_Maps;
    std::string m_Saves;
    const std::vector < std::string > m_Elements;
    int m_Highlight;
};


#endif