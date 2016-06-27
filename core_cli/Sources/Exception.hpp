#ifndef _Exception_h_
#define _Exception_h_

#include "Common.hpp"
#include "TextFile.hpp"

namespace Core
{

//class TextFile;


class Exception: public std::exception, Core::TextFile
{
public:
	explicit Exception(const std::string &description);
	virtual ~Exception();

public:
	enum ExceptionType
	{
		ExceptionCommom,
		ExceptionNoFile,
		ExceptionNotImplemented,
		ExcpetionOther

	};

	static void die(std::string description, std::string fileName);

	static void error(std::string description, std::string fileName);

	std::string getDescription();

protected:
	std::string description;
	size_t code;
};
// class Exception

class ExceptionNoFile: public Exception
{
public:
	explicit ExceptionNoFile(const std::string &description);
	virtual ~ExceptionNoFile();
};

class ExceptionNotImplemented: public Exception
{
public:
	explicit ExceptionNotImplemented(const std::string &description);
	virtual ~ExceptionNotImplemented();
};

}
#endif // #ifndef _Exception_h_

