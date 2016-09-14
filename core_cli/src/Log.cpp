/*
 * Log.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "../src/Log.hpp"

#include <fstream>
#include <sstream>
#include "../src/Exception.hpp"
#include "../src/TextFile.hpp"

namespace Core {

//static Log singletonLog = std::string("core_log.txt");
static Log *singletonLog = new Log("core_log.txt");

template<class T> std::string atos(T real) {
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
	return str;
}

Log::Log(const std::string &name) {
}

Log::~Log(void) {
}
//
//template<class T>
//Log::operator<< (T t)
//{
//
//}
void Log::operator<<(const std::string &str) {
	write(str);
}

void Log::write(const std::string &text, const std::string &fileName) {
	std::ofstream mFile;
	mFile.open(fileName.c_str());
	if (mFile.is_open()) {
		mFile << text;
		mFile.close();
	} else
		throw Exception(std::string("I can't write to") + fileName);
}

void Log::write(const std::string &text) {
	write(text, this->fileName);
	return;
}

Log* Log::getSingletonPtr(void) {
//	return &singletonLog;
	return singletonLog;
}

} /* namespace Core */
