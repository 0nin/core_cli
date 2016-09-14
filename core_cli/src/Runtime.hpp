/*
 * runtime.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_RUNTIME_H_
#define SOURCE_RUNTIME_H_

#include <string>
#include <chrono>
#include <map>

#include "../src/Common.h"
#include "../src/Log.hpp"

namespace Core {

class Runtime;
class Interval;

class Interval {
public:
	friend class Runtime;

	Interval(const std::string &name) {
		this->name = name;
	}

	virtual ~Interval() {
	}

	virtual void start() {
		begin = std::chrono::steady_clock::now();
	}

	virtual void stop() {
		end = std::chrono::steady_clock::now();
	}

	virtual std::string getName() {
		return this->name;
	}

	virtual double getMs() {
		return std::chrono::duration_cast<std::chrono::microseconds>(
				this->end - this->begin).count() / (double) 1000000.0f;
	}

	virtual double getSec() {
		return std::chrono::duration_cast<std::chrono::microseconds>(
				this->end - this->begin).count() / (double) 1000000.0f;
	}

protected:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::string name;
};

class Runtime {
public:
	Runtime(void);
	virtual ~Runtime(void);

//	static inline std::chrono::steady_clock::time_point now(void);
//	static inline void stop (std::string);
//	static inline double getMs (std::string);

	virtual void add(const std::string &point);
	virtual void start(const std::string &name);
	virtual void stop(const std::string &name);
	virtual void print(void);
	static Runtime* getSingletonPtr(void);

protected:
//	std::map <std::string, std::chrono::steady_clock::time_point> list;
//	std::map <std::string, double> list;
//	std::vector <Core::Interval> list;
	std::map<std::string, Interval> table;
};

} /* namespace core */

#endif /* SOURCE_RUNTIME_H_ */
