#include "Application.h"

#include "Exception.h"
#include "Library.h"
#include "Runtime.h"

//#include <iostream>
//#include "Exception.h"
//#include "Global.h"
//#include "Library.h"
//#include "PathList.h"
//#include "Runtime.h"

namespace Core {

#define errorNULL throw Exception( "null pointer");

Application::Application(std::string path, std::string configFile) {
	_exit = false;
	this->path = path;
	this->config = configFile;
}

Application::~Application() {
	// empty
}

void Application::init() {
	Library::getSingletonPtr()->loadConfigFile("config.conf");
}

void Application::quit() {
	this->_exit = true;
}

void Application::loop() {
	std::string in, in_prev;
	Runtime* tt = Runtime::getSingletonPtr();

	while (_exit != true) {
		printf("> ");
		std::cin >> in;
//		tt->stop(in_prev);
//		tt->start(in);
		in_prev = in;
		if (in == "exit") {
			quit();
		} else if (in == "add") {
			std::string x, y;
			std::cin >> x;
			std::cin >> y;
			if (!x.empty() && !y.empty()) {
				Library::getSingletonPtr()->addParam(x, y);
			}
		} else if (in == "show") {
			Library::getSingletonPtr()->printAll();
		} else if (in == "get") {
			std::string x;
			std::cin >> x;
			std::cout << Library::getSingletonPtr()->getParam(x) << std::endl;
		} else if (in == "start") {
			std::string x;
			std::cin >> x;
			tt->start(x);
		} else if (in == "stop") {
			std::string x;
			std::cin >> x;
			tt->stop(x);
		} else if (in == "time") {
			tt->print();
		} else {
			std::cout << "LOL:" << std::endl;
		}
		//handle(in);
	}
}

void Application::handle(std::string msg) {
	if (msg == "exit") {
		quit();
	} else if (msg.empty() || msg != "exit") {
		std::cout << "Wrong word!" << std::endl;
	}
}

void Application::kill() {
	//empty
}

void Application::go() {
//	path_list* _path = path_list::getSingletonPtr();
	//Decoder* _decoder=Decoder::getSingletonPtr();
	//_decoder->loadConfigFile( path);
	init();
	loop();
	kill();
}

}
