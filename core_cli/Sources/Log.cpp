/*
 * Log.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "Log.hpp"

namespace Core {

static Log singletonLog;

Log::Log() {
	// TODO Auto-generated constructor stub

}

Log::~Log() {
	// TODO Auto-generated destructor stub
}

Log getSingleton() {
	return singletonLog;
}
Log* getSingletonPtr() {
	return &singletonLog;
}

} /* namespace Core */
