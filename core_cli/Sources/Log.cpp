/*
 * Log.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "Log.hpp"

namespace Core
{

static Log singletonLog = std::string("core_log.txt");

Log::Log(const std::string &name) :
		TextFile(name)
{
}

Log::~Log(void)
{
}

Log getSingleton(void)
{
	return singletonLog;
}
Log* getSingletonPtr(void)
{
	return &singletonLog;
}

} /* namespace Core */
