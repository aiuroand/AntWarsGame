#ifndef LOOP_H
#define LOOP_H
#include <iostream>
#include <string>
#include "menu.h"
#include "game.h"
#include "screen.h"

enum EStatus
{
  e_Menu,
  e_Play,
  e_Rules,
  e_Exit
};

class CLoop
{
  public:
      CLoop ( std::string maps,
              std::string saves,
              std::string talents )
     : m_Maps ( maps ),
       m_Saves ( saves ),
       m_Talents ( talents ),
       m_Status ( e_Menu )
    {
      loop();
    }
 
  private:
    void loop ( void );
    std::string m_Maps;
    std::string m_Saves;
    std::string m_Talents;
    EStatus m_Status;
    CMenu m_Menu;
    CGame m_Game;
    CScreen m_Screen;

};

#endif // LOOP_H