#include "Exception.hpp"

#include "TextFile.hpp"

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
	std::string str = "Exception:: " + msg + " " + ";\n";
	std::cerr << str;
	TextFile::write(str, t_errorlog);
	eBox(msg, "Core::Exception");
	exit(1);
}

void Exception::error(std::string msg, std::string t_errorlog)
{
	std::string str = "Exception:: " + msg + " " + ";\n";
	std::cerr << str;
	TextFile::write(str, t_errorlog);
	eBox(msg, "Core::Exception");
}

Exception::Exception(const std::string &dsc)
{
	description = dsc;
}

Exception::~Exception(void)
{
}

std::string Exception::getDescription(void)
{
	return description;

}

ExceptionNoFile::ExceptionNoFile(const std::string &dsc) :
		Exception(dsc)
{

}
ExceptionNoFile::~ExceptionNoFile(void)
{

}

ExceptionNotImplemented::ExceptionNotImplemented(const std::string &dsc) :
		Exception(dsc)
{
	// TODO Auto-generated constructor stub

}

ExceptionNotImplemented::~ExceptionNotImplemented(void)
{
	// TODO Auto-generated destructor stub
}

} /* namespace Core */
