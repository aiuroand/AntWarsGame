

class CPlayer
{
  public:
    CPlayer (){};
    MakeMove (){} = 0; 
 
  protected:
    int m_Id;
    int m_Color;
};