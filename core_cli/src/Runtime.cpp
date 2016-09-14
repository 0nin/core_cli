/*
 * runtime.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "../src/Runtime.hpp"

namespace Core {

static Runtime instance;

Runtime::Runtime(void) {
}

Runtime::~Runtime(void) {
}


void Runtime::add(const std::string &name) {
	Interval* tau = new Interval(name);
//	tau->begin = begin;
	this->table.insert(std::make_pair(std::string("tt_") + name, *(tau)));
	delete tau;
}

void Runtime::start(const std::string &name) {
	auto begin = std::chrono::steady_clock::now();
	Interval* tau = new Interval(name);
	tau->begin = begin;
	this->table.insert(std::make_pair(std::string("tt_") + name, *(tau)));
	delete tau;
}

void Runtime::stop(const std::string &name) {
	auto end = std::chrono::steady_clock::now();
//	list[name]->stop();// = end;
	table.at(std::string("tt_") + name).end = end;
}
//virtual double getMs (std::string);

void Runtime::print() {
	for (auto it = table.begin(); it != table.end(); it++) {
		std::cout << it->first << " |  " << it->second.getSec() << std::endl;
	}
}

Runtime* Runtime::getSingletonPtr() {
	return &instance;
}

//Runtime Runtime::getSingleton()
//{
//	return instance;
//}

} /* namespace Core */
