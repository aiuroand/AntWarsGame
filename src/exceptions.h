#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>

class CLeave{};
class CSave{};
class CFileReadingError
{
  public:
    CFileReadingError ( std::string f )
    : m_FileName ( f )
    {}
    std::string m_FileName;
};
class CRoadDoesNotExist
{};
class CDamagedFile
{
  public:
    CDamagedFile ( int x,
                   int y )
    : m_X ( x ),
      m_Y ( y )
    {}

    int m_X;
    int m_Y;
};
#endif //EXCEPTIONS_H