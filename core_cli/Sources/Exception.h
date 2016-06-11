#ifndef _Exception_h_
#define _Exception_h_

#include "Common.h"
#include "TextFile.h"
//#include <string>
//#include <iostream>
//#include <exception>

namespace Core {

class TextFile;

class Exception
:public std::exception
{
public:
    Exception( const std::string fileName);
    virtual ~Exception();

    static void die( std::string description, std::string fileName);
    static void error( std::string description, std::string fileName);

    std::string getDescription();

protected:
    std::string description;
}; // class Exception

}
#endif // #ifndef _Exception_h_

