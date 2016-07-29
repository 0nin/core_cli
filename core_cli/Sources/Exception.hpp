#ifndef _Exception_h_
#define _Exception_h_

#include "Common.h"
//#include "TextFile.hpp"

namespace Core {

//class TextFile;

enum ExceptionType {
	ExceptionTypeCommom,
	ExceptionTypeNoFile,
	ExceptionTypeNotImplemented,
	ExceptionTypeTableMiss,
	ExcpetionTypeOther

};

class Exception: public std::exception {
public:
	explicit Exception(const std::string &description);
	explicit Exception(const std::string &description,
			Core::ExceptionType type);
	virtual ~Exception();

public:

	static void die(std::string description, std::string fileName);

	static void writeToLog(std::string description, std::string fileName);
//	static void error(std::string description, std::string fileName);

	std::string getDescription();

protected:
	std::string description;
	size_t code;
	ExceptionType type;
};
// class Exception

class ExceptionNoFile: public Exception {
public:
	explicit ExceptionNoFile(const std::string &description);
	virtual ~ExceptionNoFile();
};

class ExceptionNotImplemented: public Exception {
public:
	explicit ExceptionNotImplemented(const std::string &description);
	virtual ~ExceptionNotImplemented();
};

class ExceptionTableMiss: public Exception {
public:
	explicit ExceptionTableMiss(const std::string &description);
	virtual ~ExceptionTableMiss();
};

} /* namespace Core */
#endif // #ifndef _Exception_h_

