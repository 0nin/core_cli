#include "Exception.hpp"

#include "TextFile.hpp"
#include "Log.hpp"

#if defined __WIN32__ || _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
extern void eBox( const std::string &message, const std::string &caption)
{
	MessageBox(NULL, message.c_str(), caption.c_str(), MB_ICONERROR);
	return;
}
#else
extern void eBox(const std::string &message, const std::string &caption)
{
	return;
}
#endif

#include "Exception.hpp"

namespace Core
{

void Exception::die(std::string msg, std::string t_errorlog)
{
	std::string str = "Exception:: " + msg + " ";
	std::cerr << str << std::endl;
	TextFile::write(str, t_errorlog);
	eBox(msg, "Core::Exception");
}

void Exception::writeToLog(std::string msg, std::string t_errorlog)
{
	std::string str = "Exception:: " + msg + " ";
	std::cerr << str << std::endl;
	TextFile::write(str, t_errorlog);
}

//void Exception::error(std::string msg, std::string t_errorlog)
//{
//	std::string str = "Exception:: " + msg + " " + ";\n";
//	std::cerr << str;
//	TextFile::write(str, t_errorlog);
//	eBox(msg, "Core::Exception");
//}

Exception::Exception(const std::string &dsc) :
		description(dsc), code(0) //there is codes for exceptions for now
{
	this->type = ExceptionTypeCommom;
}

Exception::Exception(const std::string &dsc, ExceptionType type) :
		description(dsc), code(0) //there is codes for exceptions for now
{
	this->type = type;
}

Exception::~Exception(void)
{
}

std::string Exception::getDescription(void)
{
	return description;

}

ExceptionNoFile::ExceptionNoFile(const std::string &dsc) :
		Exception("")
{
	this->type = ExceptionTypeNoFile;
	this->description = std::string("ExceptionNoFile:: ") + "Can't find file:: " + dsc;
}
ExceptionNoFile::~ExceptionNoFile(void)
{

}

ExceptionNotImplemented::ExceptionNotImplemented(const std::string &dsc) :
		Exception(dsc)
{
	this->type = ExceptionTypeNotImplemented;
}

ExceptionNotImplemented::~ExceptionNotImplemented(void)
{
}

ExceptionTableMiss::ExceptionTableMiss(const std::string &dsc) :
		Exception(dsc)
{
	this->type = ExceptionTypeTableMiss;
}

ExceptionTableMiss::~ExceptionTableMiss()
{
}

} /* namespace Core */
