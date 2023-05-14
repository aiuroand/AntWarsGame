#include "1mapelem.h"

class CAntHill: public CMapElem
{
  public:
    CAntHill() : CMapElem() {};
    print ();

  protected:
    int m_BirthFrequency;
}