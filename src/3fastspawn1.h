#include "3talent.h"

class CFastSpawn : public CTalent
{
  public:
    CFastSpawn() : CTalent(){};
    useTalent();

  private:
    int m_Id;
    std::string m_Description;
}