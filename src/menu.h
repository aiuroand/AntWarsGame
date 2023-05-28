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
#include "exceptions.h"

class CMenu
{
  public:
    /*! Constructor.
     *  @param screen - main game screen.
     *  @param status - current game status.
     *  @param maps   - directory with maps.
     *  @param saves  - directory with saved maps.
     */
    CMenu ( CScreen * screen,
            EStatus & status,
            std::string maps,
            std::string saves )
    : m_HighlightMaps ( 0 ),
      m_HighlightSaves ( 0 ),
      m_Screen ( screen ),
      m_Status ( status ),
      m_Maps ( maps ), 
      m_Saves ( saves ), 
      m_Elements ( { "New Game", "Saved Games", "Rules", "Exit" } ),
      m_Highlight ( 0 )
    {
      
    }

    /*! Main menu loop that is used to choose it's elements.
     */
    void loop ( void );

    /*! Maps menu loop that is used to choose game map.
     *  @throw CFileReadingError if there was a problem during file or directory reading.
     */
    void chooseNewMap ( void );
    
    /*! Saves menu loop that is used to choose saved game map.
     *  @throw CFileReadingError if there was a problem during file or directory reading.
     */
    void continueMap ( void );
    
    //! Represents current cursor position in "New Game" menu.
    int m_HighlightMaps;
    //! Represents current cursor position in "Saved Games" menu.
    int m_HighlightSaves;

  private:

    CScreen * m_Screen;
    EStatus & m_Status;
    std::string m_Maps;
    std::string m_Saves;
    //! Represents menu elements 
    const std::vector < std::string > m_Elements;
    //! Represents current cursor position in Main menu.
    int m_Highlight;
};


#endif