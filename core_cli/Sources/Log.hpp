/*
 * Log.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_LOG_H_
#define SOURCE_LOG_H_

#include "Common.hpp"

//#include "Uncopy.h"

namespace Core {

class Log: public Uncopy {
public:
	Log();
	virtual ~Log();

	static Log getSingleton();
	static Log* getSingletonPtr();
};

} /* namespace Core */

#endif /* SOURCE_LOG_H_ */
