#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include "coords.h"
#include <ncurses.h>
#include "screen.h"
#include "map.h"
#include "exceptions.h"

/*! Child class that represents human player 
 */
class CHuman : public CPlayer
{
  public:
    /*! Constructor that firtsly constructs parent class CPlayer
     *  @param color  - color of player
     *  @param screen - main screen to print on
     */
    CHuman ( char color,
             CScreen * screen )
    : CPlayer( color ),
      m_Screen ( screen )
    {};
    
    /*! Overrided method that is used to collect moves from human player
     *  @param  - current game's map
     *  @return std::pair < int , int > where: first number is human anthill's id, 
     *                                         second is target anthill's id
     */
    std::pair < int, int > makeMove ( CMap & map ) override;

    /*! Overrided method that allows human player to select talents
     *  @param map - current game's map
     *  @param t   - std::list of pointers to abstract CTalent player should choose talent from
     */
    void selectTalent ( CMap & map, std::list < CTalent * > & t ) override;

  private:

    /*! Private method that reads user's mouse input 
     *  @return coords where user clicked with his left mouse button, that are represented by CCoords
     *  @throw CLeave class if user pressed 'q' button 
     *  @throw CSave  class if user pressed 's' button
     */
    CCoords readMouse ( void );

    CScreen * m_Screen;
};
#endif // HUMAN_H