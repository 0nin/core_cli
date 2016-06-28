/*
 * Log.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_LOG_H_
#define SOURCE_LOG_H_

#include "Common.hpp"

namespace Core
{

class Log
{
public:
	Log(const std::string &name);
	virtual ~Log(void);

	void print();

	virtual void write(std::string &text);

	static void write(std::string &text, std::string &name);

//	static Log getSingleton();
	static Log* getSingletonPtr(void);

private:
	std::string fileName;
};

} /* namespace Core */

#endif /* SOURCE_LOG_H_ */
