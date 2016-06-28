/*
 * Engine.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: avs
 */

#include "Engine.hpp"

#include "Runtime.hpp"
#include "CfgTable.hpp"
#include "PathList.hpp"
#include "Log.hpp"

namespace Core
{

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
}

void Engine::clear(void)
{
//	delete Log::getSingletonPtr();
//	delete PathList::getSingletonPtr();
//	delete Runtime::getSingletonPtr();
//	delete CfgTable::getSingletonPtr();
}

void Engine::go(void)
{
	init();
	loop();
	clear();
	kill();
}

} /* namespace Core */
