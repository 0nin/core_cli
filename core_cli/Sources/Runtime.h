/*
 * runtime.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_RUNTIME_H_
#define SOURCE_RUNTIME_H_

//#include "Common.h"
//#include "Interval.h"

#include "Interval.h"
#include "Common.h"
#include "Log.h"

#include <string>
#include <chrono>
#include <map>

namespace Core {

class Runtime : public Log {
public:
	explicit Runtime();
	virtual ~Runtime();

	static inline std::chrono::steady_clock::time_point now ();
//	static inline void stop (std::string);
//	static inline double getMs (std::string);

	virtual void add (std::string);
	virtual void start (std::string);
	virtual void stop (std::string);

	virtual void print ();

	static Runtime* getSingletonPtr();
	static Runtime getSingleton();

protected:
//	std::map <std::string, std::chrono::steady_clock::time_point> list;
//	std::map <std::string, double> list;
//	std::vector <Core::Interval> list;
	std::map <std::string, Core::Interval> table;
};

} /* namespace core */

#endif /* SOURCE_RUNTIME_H_ */
