/*
 * Log.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "Log.hpp"
#include "TextFile.hpp"
#include "Exception.hpp"

#include <fstream>
#include <sstream>

namespace Core
{

static Log singletonLog = std::string("core_log.txt");

template<class T> std::string atos(T real)
{
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
	return str;
}

Log::Log(const std::string &name)
{
}

Log::~Log(void)
{
}


void Log::write(std::string &text, std::string &fileName)
{
	std::ofstream mFile;
	mFile.open(fileName.c_str());
	if (mFile.is_open())
	{
		mFile << text;
		mFile.close();
	}
	else
		throw Exception(std::string("I can't write to") + fileName);
}

void Log::write(std::string &text)
{
	write(text, this->fileName);
	return;
}

Log* Log::getSingletonPtr(void)
{
	return &singletonLog;
}

} /* namespace Core */
