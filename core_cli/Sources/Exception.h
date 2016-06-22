#ifndef _Exception_h_
#define _Exception_h_

#include "Common.hpp"
#include "TextFile.hpp"
//#include <string>
//#include <iostream>
//#include <exception>

namespace Core {

class TextFile;

class Exception
:public std::exception, Core::TextFile
{
public:
	explicit Exception(const std::string fileName);
    virtual ~Exception();

    static void die( std::string description, std::string fileName);
    static void error( std::string description, std::string fileName);

    std::string getDescription();

protected:
    std::string description;
}; // class Exception

class ExceptionNoFile: public Exception {
public:
	explicit ExceptionNoFile (const std::string fileName);
	virtual ~ExceptionNoFile();
};

}
#endif // #ifndef _Exception_h_

