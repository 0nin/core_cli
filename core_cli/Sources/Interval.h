/*
 * Interval.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_INTERVAL_H_
#define SOURCE_INTERVAL_H_

#include "Common.h"

#include "Uncopy.h"

#include <string>
#include <chrono>

namespace Core {

class Runtime;

class Interval: public Uncopy {
public:
	friend class Core::Runtime;

	explicit Interval(std::string name);

	virtual ~Interval();

	virtual void start ();

	virtual void stop();

	virtual std::string getName();

	virtual double getMs();

	virtual double getSec();

protected:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::string name;
};

} /* namespace Core */

#endif /* SOURCE_INTERVAL_H_ */
