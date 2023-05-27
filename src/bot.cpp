#include "bot.h"

std::pair < int, int > CBot::makeMove ( CMap & map )
{
  int first = map . getStrongest( m_Color );

  mvwprintw( m_Screen -> m_Window, 2, 42, "%d", first );
  wrefresh ( m_Screen -> m_Window );

  int second = map . getWeakest( m_Color );

  mvwprintw( m_Screen -> m_Window, 2, 44, "%d", second );
  wrefresh ( m_Screen -> m_Window );
    
  return std::make_pair( first, second );
}

void CBot::selectTalent (  CMap & map, std::list < CTalent * > & t )
{

}