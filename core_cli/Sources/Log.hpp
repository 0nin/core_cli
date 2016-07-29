/*
 * Log.h
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#ifndef SOURCE_LOG_H_
#define SOURCE_LOG_H_

#include "Common.h"

namespace Core {

class Log {
public:
	explicit Log(std::string const &name);

	virtual ~Log(void);

//	template <class T> operator<< (T t);
	void operator<<(std::string const &str);

	virtual void write(std::string const &text);

	static void write(std::string const &text, std::string const &name);

//	static Log getSingleton();
	static Log* getSingletonPtr(void);

private:
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log& operator =(Log const&) = delete;
	Log& operator =(Log&&) = delete;

	void print();

	std::string fileName;
};

} /* namespace Core */

#endif /* SOURCE_LOG_H_ */
