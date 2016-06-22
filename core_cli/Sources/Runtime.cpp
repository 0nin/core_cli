/*
 * runtime.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: avs
 */

#include "Runtime.hpp"

namespace Core {

static Runtime instance;

Runtime::Runtime() {
	// TODO Auto-generated constructor stub

}

Runtime::~Runtime() {
	// TODO Auto-generated destructor stub
}


inline std::chrono::steady_clock::time_point Runtime::now () {
	return std::chrono::steady_clock::now();
}

void Runtime::add (std::string name) {
	Interval* tau = new Interval(name);
//	tau->begin = begin;
	this->table.insert (std::make_pair (std::string("tt_")+name, *(tau)));
	delete tau;
}

void Runtime::start (std::string name) {
	auto begin = std::chrono::steady_clock::now();
	Interval* tau = new Interval(name);
	tau->begin = begin;
	this->table.insert (std::make_pair (std::string("tt_")+name, *(tau)));
	delete tau;
}

void Runtime::stop (std::string name) {
	auto end = std::chrono::steady_clock::now();
//	list[name]->stop();// = end;
	table.at(std::string("tt_")+name).end = end;
}
//virtual double getMs (std::string);

void Runtime::print () {
	for (auto it = table.begin(); it != table.end(); it++) {
		std::cout << it->first << " |  " << it->second.getSec() << std::endl;
	}
}

Runtime* Runtime::getSingletonPtr() {
	return &instance;
}

Runtime Runtime::getSingleton() {
	return instance;
}

} /* namespace Core */
