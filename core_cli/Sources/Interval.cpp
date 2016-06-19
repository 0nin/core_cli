/*
 * Interval::Interval.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "Interval.hpp"

namespace Core {

Interval::Interval(std::string name) {
//	this->begin = std::chrono::steady_clock::now();
	this->name = name;
}

Interval::~Interval() {
}

void Interval::start() {
	begin = std::chrono::steady_clock::now();
}

void Interval::stop() {
	end = std::chrono::steady_clock::now();
}

std::string Interval::getName() {
	return this->name;
}

double Interval::getMs() {
	return std::chrono::duration_cast <std::chrono::microseconds> (this->end - this->begin).count() / (double) 1000000.0f;
}

double Interval::getSec() {
	return std::chrono::duration_cast <std::chrono::microseconds> (this->end - this->begin).count() / (double) 1000000.0f;
}


} /* namespace Core */
