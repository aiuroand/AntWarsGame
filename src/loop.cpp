#include "loop.h"

void CLoop::loop ( void )
{
  while ( 1 )
  {
    if ( m_Status == e_Menu )
    {
      try
      {
        m_Menu . loop();
      }
      catch ( CFileReadingError & f )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", f . m_FileName . c_str() );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
        m_Status = e_Exit;
      }
    }
    else if ( m_Status == e_NewGame )
    {
      // Making "beatuful" files names without 'maps/' in map selecting menu
      char str[100];
      int i = 0;
      try
      {
        for ( const auto & it : std::filesystem::directory_iterator ( m_Maps ) )
        {
          if ( i == m_Menu . m_HighlightMaps )
          {
            memcpy ( str,
                     it . path() . c_str() + m_Maps . size() + 1,
                     strlen ( it . path() . c_str() + m_Maps . size() + 1 ) + 1 );
            break;
          }
          i++;
        }
      }
      catch ( ... )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", m_Maps . c_str() );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
        m_Status = e_Menu;
      }

      std::string newStr( str );
      
      // Creating new game and entering its loop
      try
      {
        m_Game = new CGame ( m_Maps + "/" + newStr, m_Saves, m_Talents, m_Screen ); 
        m_Game -> loop();
      }
      catch ( CFileReadingError & f )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", f . m_FileName . c_str() );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "Expected maps file." );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      catch ( CRoadDoesNotExist & r )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "Some roads does not exist." );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      catch ( CDamagedFile & d )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "File is damaged on position ( %d, %d )", d . m_X, d . m_Y );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      //Cleaning after leaving the game
      delete m_Game;
      m_Game = nullptr;
      m_Status = e_Menu;
    }
    else if ( m_Status == e_ContinueGame )
    {
      // Making "beatuful" files names without 'saves/' in saves selecting menu
      char str[100];
      int i = 0;
      try
      {
        for ( const auto & it : std::filesystem::directory_iterator ( m_Saves ) )
        {
          if ( i == m_Menu . m_HighlightSaves )
          {
            memcpy ( str,
                     it . path() . c_str() + m_Maps . size() + 1,
                     strlen ( it . path() . c_str() + m_Maps . size() + 1 ) + 1 );
            break;
          }
          i++;
        }
      }
      catch ( ... )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", m_Saves . c_str() );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
        m_Status = e_Menu;
      }
      std::string newStr( str );

      // Creating new game and enering its loop
      try
      {
        m_Game = new CGame ( m_Saves + "/" + newStr, m_Saves, m_Talents, m_Screen );
        m_Game -> loop();
      }
      catch ( CFileReadingError & f )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", f . m_FileName . c_str() );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "Expected saves file." );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      catch ( CRoadDoesNotExist & r )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "Some roads does not exist." );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      catch ( CDamagedFile & d )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "File is damaged on position ( %d, %d )", d . m_X, d . m_Y );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }

      // Cleaning after leaving the game
      delete m_Game;
      m_Game = nullptr;
      m_Status = e_Menu;
    }
    else if ( m_Status == e_Rules )
    {
      try
      {
        m_Rules . loop();
      }
      catch ( CFileReadingError & f )
      {
        wclear ( m_Screen -> m_Window );
        mvwprintw ( m_Screen -> m_Window, 0, 0, "Error while reading file: \"%s\"", f . m_FileName . c_str() );
        mvwprintw ( m_Screen -> m_Window, 1, 0, "Expected rules file." );
        wrefresh ( m_Screen -> m_Window );
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
      }
      m_Status = e_Menu;
    }
    else if ( m_Status == e_Exit )
      return;
  }
}