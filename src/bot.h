#ifndef BOT_H
#define BOT_H

#include "player.h"
#include "coords.h"
#include "ncurses.h"
#include "screen.h"
#include "map.h"

/*! Child class that represents bot player 
 */
class CBot: public CPlayer
{
  public:
    /*! Constructor that firtsly constructs parent class CPlayer
     *  @param color  - color of bot player
     *  @param screen - main screen to print on
     */
    CBot ( char color,
           CScreen * screen )
    : CPlayer( color ),
      m_Screen ( screen )
    {};
    
    /*! Overrided method that is used to collect moves from bot player.
     *  Bot selects his strongest anthill ant tries to attack the weakest
     *  emenies' anthill on the map.
     *  @param  - current game's map
     *  @return std::pair < int , int > where: first number is bot's anthill's id, 
     *                                         second is target anthill's id
     */
    std::pair < int, int > makeMove ( CMap & map ) override;
    
    /*! Overrided method that allows bot player to select talents
     *  @param map - current game's map
     *  @param t   - std::list of pointers to abstract CTalent bot should choose talent from
     */
    void selectTalent (  CMap & map, std::list < CTalent * > & t ) override;

  private:

    CScreen * m_Screen;
};
#endif // BOT_H