#include "game.h"

void CGame::loop ( void )
{

  readTalents();
  setPlayers();

  m_Map . print();
  printHud();
  while ( 1 )
  {
    try 
    {
      if ( m_Map . getRound() == m_Tier1Time )
        for ( const auto & it : m_Players )
          it -> selectTalent ( m_Map, m_Tier1 );
      
      if ( m_Map . getRound() == m_Tier2Time )
        for ( const auto & it : m_Players )
          it -> selectTalent ( m_Map, m_Tier2 );
    }
    catch ( CLeave & x )
    {
      return;
    }    
    // if ( m_Map . getRound() == m_Tier3Time )
    //   for ( const auto & it : m_Players )
    //     it -> selectTalent ( m_Map, m_Tier3 );
    

    for ( const auto & it : m_Players )
      it -> activateTalents ( it -> getColor(), m_Map );

    m_Map . print();
    printHud();

    std::list < std::pair < int, int > > orders;
  
    try 
    {
      for ( const auto & it : m_Players )
        orders . push_back ( it -> makeMove( m_Map ) );
    }
    catch ( CLeave & x )
    {
      return;
    }
    m_Map . clearRoads();  
    
    for ( const auto & it : orders )
      m_Map . fillRoad ( it . first, it . second );

    printHud();
    m_Map . attack();
    m_Map . createAnts();
    m_Map . print();
    removeDead();
    printHud();
    
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    char c;
    if ( ( c = m_Map . checkWinner() ) != 'n' )
    {
      mvwprintw ( m_Screen -> m_Window, 10, 10, "%c won", c );
      wrefresh( m_Screen -> m_Window );
      std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
      break;
    }
    m_Map . deactivateAll();
    m_Map . setRound ( m_Map . getRound () + 1 ) ;
  }
}

void CGame::removeDead( void )
{
  for ( auto it = m_Players . begin(); it != m_Players . end(); )
    if ( m_Map . countHills ( (*it) -> getColor() ) == 0 )
    {
      delete (*it);
      it = m_Players . erase ( it );
    }
    else
      it++;
}

void CGame::printHud ( void )
{

  // mvwprintw ( m_Screen -> m_Window, 1, m_Map . getWidth() + 1, "|         |" );
  // mvwprintw ( m_Screen -> m_Window, 2, m_Map . getWidth() + 1, "|   ~|~   |" );
  // mvwprintw ( m_Screen -> m_Window, 3, m_Map . getWidth() + 1, "|  ~~|~~  |" );
  // mvwprintw ( m_Screen -> m_Window, 4, m_Map . getWidth() + 1, "| ~~~|~~~ |" );
  // mvwprintw ( m_Screen -> m_Window, 5, m_Map . getWidth() + 1, "|    |    |" );
  // mvwprintw ( m_Screen -> m_Window, 6, m_Map . getWidth() + 1, "|   / \\   |" );
  // mvwprintw ( m_Screen -> m_Window, 7, m_Map . getWidth() + 1, "+---------+" );
  mvwprintw ( m_Screen -> m_Window, 0, m_Map . getWidth() + 1, "+---------+" );
  mvwprintw ( m_Screen -> m_Window, 1, m_Map . getWidth() + 1, "| Round " );
  mvwprintw ( m_Screen -> m_Window, 1, m_Map . getWidth() + 9, "%d", m_Map . getRound() );
  mvwprintw ( m_Screen -> m_Window, 1, m_Map . getWidth() + 11, "|" );
  mvwprintw ( m_Screen -> m_Window, 2, m_Map . getWidth() + 1, "+---------+" );
  wrefresh ( m_Screen -> m_Window );
}

void CGame::readTalents( void )
{
  std::ifstream ifs;
  std::string name, description, str1, str2, str3;
  int i, j, k;

  ifs . open ( m_Talents + "/time.txt", std::ios::in );
  std::getline ( ifs, str1 );
  std::getline ( ifs, str2 );
  std::getline ( ifs, str3 );
  m_Tier1Time = (int) str1[0] - 48;
  m_Tier2Time = (int) str2[0] - 48;
  m_Tier3Time = (int) str3[0] - 48;
  ifs . close();

  ifs . open ( m_Talents + "/moreants.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier1 . push_back ( new CMoreAnts ( name, description, i ) );
  ifs . close();

  ifs . open ( m_Talents + "/morearmor.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier1 . push_back ( new CMoreArmor ( name, description, i ) );
  ifs . close();

  ifs . open ( m_Talents + "/moremax.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier2 . push_back ( new CMoreMax ( name, description, i ) );
  ifs . close();

  ifs . open ( m_Talents + "/moremove.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier2 . push_back ( new CMoreMove ( name, description, i ) );
  ifs . close();


  // int amount = (int) str1[0] - 48;
  // mvwprintw ( m_Screen -> m_Window, 1, 1, "%d", i );
  // wrefresh ( m_Screen -> m_Window );
  // while ( 1)
  // {
  //   /* code */
  // }

}

void CGame::setPlayers ( void )
{
    for ( const auto & it : m_Map . m_Players )
    {
      if ( it . first == 'g' )
      {
        m_Players . push_back ( new CHuman ( it . first, m_Screen ) );
             if ( it . second & 1 )
          m_Players . back() -> addTalent ( m_Tier1 . front() );
        else if ( it . second & 2 )
          m_Players . back() -> addTalent ( m_Tier1 . back() );
        else if ( it . second & 4 )
          m_Players . back() -> addTalent ( m_Tier2 . front() );
        else if ( it . second & 8 )
          m_Players . back() -> addTalent ( m_Tier2 . back() );
        else if ( it . second & 16 )
          m_Players . back() -> addTalent ( m_Tier3 . front() );
        else if ( it . second & 32 )
          m_Players . back() -> addTalent ( m_Tier3 . back() );
      }
      else if ( it . first != 'g' && it . first != 'w' )
      {
        m_Players . push_back ( new CBot ( it . first, m_Screen ) );
             if ( it . second & 1 )
          m_Players . back() -> addTalent ( m_Tier1 . front() );
        else if ( it . second & 2 )
          m_Players . back() -> addTalent ( m_Tier1 . back() );
        else if ( it . second & 4 )
          m_Players . back() -> addTalent ( m_Tier2 . front() );
        else if ( it . second & 8 )
          m_Players . back() -> addTalent ( m_Tier2 . back() );
        else if ( it . second & 16 )
          m_Players . back() -> addTalent ( m_Tier3 . front() );
        else if ( it . second & 32 )
          m_Players . back() -> addTalent ( m_Tier3 . back() );
      } 
    }
}