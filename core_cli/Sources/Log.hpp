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

class Log : public Core::TextFile {
public:
	Log();
	virtual ~Log();

	static Log getSingleton();
	static Log* getSingletonPtr();
};

} /* namespace Core */

#endif /* SOURCE_LOG_H_ */
