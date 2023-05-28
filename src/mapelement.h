#ifndef MAP_ELEM
#define MAP_ELEM

#include "coords.h"
#include "screen.h"

/*! Abstract class that represents an object on game's map 
 */
class CMapElem
{
  public:
    /*! Constructior
     *  @param c      - color of object's owner
     *  @param coords - object's location, that is represented using CCoords class
     */
    CMapElem( char c,
              CCoords coords )
    : m_Color ( c ),          
      m_Coords ( coords )
    {};

    /*! Virtual destructor
     */
    virtual ~CMapElem( void ) = default;
    
    /*! Abstract method that is used to print an object on the screen
     *  @param sct - screen, represented by CScreen class, where object should be drawn on
     */
    virtual void print ( CScreen * scr ) const = 0;

    /*! Abstract method that is used to get the object in char format
     *  @return char value that represents the object
     */
    virtual char get ( void ) const = 0;

    /*! Gets coords of an object represented using CCoords class
     *  @return coords of the object
     */
    inline CCoords getCoords ( void ) const
    {
      return m_Coords;
    }

  protected: 

    char m_Color;
    CCoords m_Coords;
};

#endif // MAP_ELEM