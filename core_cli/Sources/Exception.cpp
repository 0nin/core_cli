#include "Exception.hpp"

#include "TextFile.hpp"

#if defined __WIN32__ || _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
extern void eBox( std::string message, std::string caption) {
	MessageBox(NULL, message.c_str(), caption.c_str(), MB_ICONERROR);
	return;
}
#else
extern void eBox(std::string message, std::string caption) {
	return;
}
#endif

//#include <stdlib.h>
//#include <iostream>

//using namespace std;
//using namespace Core;

namespace Core {

void Exception::die(std::string msg, std::string t_errorlog) {
	std::string str = "mp::Exception: " + msg + " " + ";\n";
	std::cout << str;
	TextFile::write(str, t_errorlog);
	eBox(msg, "Exception");
	//SDL_Quit();
	exit(1);
}

void Exception::error(std::string msg, std::string t_errorlog) {
	std::string str = "mp::Exception: " + msg + " " + ";\n";
	std::cout << str;
	TextFile::write(str, t_errorlog);
	eBox(msg, "Exception");
}

Exception::Exception(const std::string dsc) {
	description = dsc;
}

Exception::~Exception() {
}

std::string Exception::getDescription() {
	return description;

}

ExceptionNoFile::ExceptionNoFile (const std::string fileName) :
	Exception(fileName){

}
ExceptionNoFile::~ExceptionNoFile(){

}


} /* namespace Core */
