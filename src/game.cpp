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
      if ( m_Map . getRound() == m_Tier1Time && m_Players . front() -> getTalentsSize() == 0 )
        for ( const auto & it : m_Players )
          it -> selectTalent ( m_Map, m_Tier1 );
      
      if ( m_Map . getRound() == m_Tier2Time && m_Players . front() -> getTalentsSize() == 1  )
        for ( const auto & it : m_Players )
          it -> selectTalent ( m_Map, m_Tier2 );

      if ( m_Map . getRound() == m_Tier3Time && m_Players . front() -> getTalentsSize() == 2  )
        for ( const auto & it : m_Players )
          it -> selectTalent ( m_Map, m_Tier3 );
    }
    catch ( CLeave & x )
    {
      return;
    }
    catch ( CSave & x )
    {
      saveGame();
      return;
    }
    
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
    catch ( CSave & x )
    {
      saveGame();
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
  int i;

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

  ifs . open ( m_Talents + "/conqueror.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier3 . push_back ( new CConqueror ( name, description, i ) );
  ifs . close();

  ifs . open ( m_Talents + "/max.txt", std::ios::in );
  std::getline ( ifs, name );
  std::getline ( ifs, description );
  std::getline ( ifs, str1 );
  i = (int) str1[0] - 48;
  m_Tier3 . push_back ( new CMaxAnts ( name, description, i ) );
  ifs . close();

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

void CGame::saveGame ( void )
{
  //https://stackoverflow.com/questions/16357999/current-date-and-time-as-string
  std::ostringstream oss;
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
  auto str = oss.str();
  
  std::ofstream ofs;
  ofs . open ( m_Saves + "/" + str , std::ios::out );
  ofs . put ( m_Map . getHeight() / 10 + 48 );
  ofs . put ( m_Map . getHeight() % 10 + 48 );
  ofs . put ( ' ' );
  ofs . put ( m_Map . getWidth() / 10 + 48 );
  ofs . put ( m_Map . getWidth() % 10 + 48 );
  ofs . put ( ' ' );
  ofs . put ( ( m_Map . getRound() - 1 ) / 10 + 48 );
  ofs . put ( ( m_Map . getRound() - 1 ) % 10 + 48 );
  ofs . put ( '\n' );

  for ( auto & it : m_Map . m_Players )
  {
    for ( const auto & it1 : m_Players )
    {
      if ( it . first == it1 -> getColor() )
      {
        char color = it . first;
        m_Map . m_Players . erase ( std::make_pair ( it . first, it . second ) );
        m_Map . m_Players . insert ( std::make_pair ( color, it1 -> countTalents( m_Tier1, m_Tier2, m_Tier3 ) ) );
      }
    }
  }
  std::vector<std::vector< std::pair <char, bool> > > map( m_Map . getHeight(), std::vector< std::pair <char, bool> >( m_Map . getWidth() ) );
  m_Map . save( map );

  for ( int i = 0; i < m_Map . getHeight(); ++i )
  { 
    for ( int j = 0; j < m_Map . getWidth(); ++j )
    {
      ofs . put ( map[i][j] . first );
    }
    ofs . put ( '\n' );
  }
}