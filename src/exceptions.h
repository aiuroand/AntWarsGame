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

#endif //EXCEPTIONS_H