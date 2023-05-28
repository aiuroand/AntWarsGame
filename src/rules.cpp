#include "rules.h"

void CRules::loop ( void )
{
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  m_Screen -> screenBox();

  int cnt = 1;
  std::ifstream ifs ( m_Dir, std::ios::in );
  if ( ifs . bad() || ifs . fail() )
  {
    throw CFileReadingError ( m_Dir );
  }

  std::string str;

  while ( !ifs . eof() )
  {
    std::getline ( ifs, str );
    mvwprintw ( m_Screen -> m_Window, cnt++, 2, "%s", str . c_str() );
  }
  
  mvwprintw ( m_Screen -> m_Window, cnt + 3, 2, "%s", "Press \'q\' to continue..." );

  while ( 1 )
  {
    char symbol = wgetch( m_Screen -> m_Window );
    switch ( symbol )
    {
      case 'q':
        return;
      default:
        continue;
    }
  }
}