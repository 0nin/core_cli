/*
 * Log.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_LOG_H_
#define SOURCE_LOG_H_

#include "Common.hpp"
#include "TextFile.hpp"

namespace Core {

class Log : public TextFile {
public:
	Log(const std::string &name);
	virtual ~Log(void);

//	static Log getSingleton();
	static Log* getSingletonPtr(void);
};

} /* namespace Core */

#endif /* SOURCE_LOG_H_ */
