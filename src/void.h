#ifndef VOID_H
#define VOID_H
#include "mapelement.h"
#include "coords.h"
#include "screen.h"

/*! Child class of CMapElem that represents void.
 */
class CVoid : public CMapElem
{
  public:
    /*! Constructor that firtsly constructs parent class CMapElem.
     *  Owner for parent class in 'n' - nobody.
     *  @param coords  - coords of the void.
     */
      CVoid ( CCoords coord )
     : CMapElem ( 'n', coord )
    {}

    /*! Destructor 
     */
    ~CVoid ( void ) = default;
    
    /*! Overrided method that is used to print an object on the screen.
     *  @param sct - screen, represented by CScreen class, where object should be drawn on.
     */
    void print ( CScreen * scr ) const override
    {
      scr -> screenPrint ( m_Coords, " " );
    }

    /*! Overrided method that is used to get the object in char format.
     *  @return char value that represents the object.
     */
    char get ( void ) const override 
    {
      return ' ';
    }
};

#endif // VOID_H