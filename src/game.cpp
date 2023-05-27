#include "game.h"

void CGame::loop ( void )
{
  readTalents();
  m_Map . print();
  printHud();
  
  for ( const auto & it : m_Map . m_Players )
    if ( it == 'g' ) 
      m_Players . push_back( new CHuman ( it, m_Screen ) );
    else if ( it != 'g' && it != 'w' )
      m_Players . push_back ( new CBot ( it, m_Screen ) );
      

  while ( 1 )
  {
    
    if ( m_Round == m_Tier1Time )
      for ( const auto & it : m_Players )
        it -> selectTalent ( m_Map, m_Tier1 );
    
    for ( const auto & it : m_Players )
      it -> activateTalents ( it -> getColor(), m_Map );

    printHud();
    m_Map . print();

    std::list < std::pair < int, int > > orders;
  
    for ( const auto & it : m_Players )
      orders . push_back ( it -> makeMove( m_Map ) );
 
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
    ++m_Round;
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
  mvwprintw ( m_Screen -> m_Window, 0, m_Map . getWidth() + 1, "+---------+" );
  mvwprintw ( m_Screen -> m_Window, 1, m_Map . getWidth() + 1, "|         |" );
  mvwprintw ( m_Screen -> m_Window, 2, m_Map . getWidth() + 1, "|   ~|~   |" );
  mvwprintw ( m_Screen -> m_Window, 3, m_Map . getWidth() + 1, "|  ~~|~~  |" );
  mvwprintw ( m_Screen -> m_Window, 4, m_Map . getWidth() + 1, "| ~~~|~~~ |" );
  mvwprintw ( m_Screen -> m_Window, 5, m_Map . getWidth() + 1, "|    |    |" );
  mvwprintw ( m_Screen -> m_Window, 6, m_Map . getWidth() + 1, "|   / \\   |" );
  mvwprintw ( m_Screen -> m_Window, 7, m_Map . getWidth() + 1, "+---------+" );
  mvwprintw ( m_Screen -> m_Window, 8, m_Map . getWidth() + 1, "+ Round " );
  mvwprintw ( m_Screen -> m_Window, 8, m_Map . getWidth() + 9, "%d %d", m_Round, m_Tier1Time );
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
  m_Tier1 . push_back ( new CMoreAnts ( name, description, j ) );
  ifs . close();

  ifs . open ( m_Talents + "/moreants.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier1 . push_back ( new CMoreAnts ( name, description, j ) );
  ifs . close();
  // amount = (int) amountStr[0] - 48;
  // mvwprintw ( m_Screen -> m_Window, 1, 1, "%d", amount );
  // wrefresh ( m_Screen -> m_Window );
  // while ( 1)
  // {
  //   /* code */
  // }

}