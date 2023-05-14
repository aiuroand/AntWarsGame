

class CMapElem
{
  public:
    CMapElem() {};
    print () = 0;

  protected:
    int m_Id;
    int m_IdOwner;
    CCoords m_Coords;
};