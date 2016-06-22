/*
 * Engine.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: avs
 */

#include "Engine.hpp"

namespace Core {

Engine::Engine() {
	// TODO Auto-generated constructor stub

}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::go() {
	init();
	loop();
	kill();

}

} /* namespace Core */
