#ifndef LOOP_H
#define LOOP_H
#include <iostream>
#include <string>
#include <cstring>
#include "menu.h"
#include "game.h"
#include "screen.h"
#include "status.h"
#include "rules.h"

class CLoop
{
  public:
      CLoop ( std::string maps,
              std::string saves,
              std::string talents,
              std::string rules )
     : m_Maps ( maps ),
       m_Saves ( saves ),
       m_Talents ( talents ),
       m_Screen ( new CScreen() ),
       m_Status ( e_Menu ),
       m_Menu ( m_Screen, m_Status, m_Maps, m_Saves ),
       m_Game ( nullptr ),
       m_Rules ( m_Screen, m_Status, rules )
    {
      loop();
    }
 
  private:
    void loop ( void );
    std::string m_Maps;
    std::string m_Saves;
    std::string m_Talents;
    CScreen * m_Screen;
    EStatus m_Status;
    CMenu m_Menu;
    CGame * m_Game;
    CRules m_Rules;
};

#endif // LOOP_H