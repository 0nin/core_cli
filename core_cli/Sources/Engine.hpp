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
	explicit Engine();
	virtual ~Engine();

//protected:
	virtual void init() = 0;

	virtual void loop() = 0;

	virtual void kill() = 0;

	virtual void quit() = 0;

	void go();
};

} /* namespace Core */

#endif /* ENGINE_HPP_ */
