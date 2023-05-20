#include "mapelement.h"

class CVoid : public CMapElem
{
  public:
      CVoid( char owner,
             CCoords coord )
     : CMapElem( owner,
                 coord ) {};
    void print ( void ) override
    {

    }

  protected:

}