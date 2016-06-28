/*
 * Engine.h
 *
 *  Created on: Jun 13, 2016
 *      Author: avs
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Common.hpp"

namespace Core
{

class Engine
{
public:
	explicit Engine(void);
	virtual ~Engine(void);

//protected:
	virtual void init(void) = 0;

	virtual void loop(void) = 0;

	virtual void kill(void) = 0;

	virtual void quit(void) = 0;

	void clear(void);

	void go(void);
};

} /* namespace Core */

#endif /* ENGINE_HPP_ */
