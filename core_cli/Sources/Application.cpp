#include "Application.hpp"

#include "Global.h"
#include "Library.hpp"
#include "Runtime.hpp"
#include "Console.hpp"
#include "Exception.hpp"
#include "PathList.hpp"

#define GREET "(core)"


namespace Core {
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

Application::Application(std::string path, std::string configFile) :
		cs("(core)") {
	_exit = false;
	this->path = path;
	this->config = configFile;
}

Application::~Application(void) {
// empty
}

void Application::init(void) {
	Library::getSingletonPtr()->loadConfigFile("config.conf");

	cs.registerCommand("info", info);
	cs.registerCommand("calc", calc);
	cs.registerCommand("plot", plot);
	cs.registerCommand("csv2dat", csv2dat);
	cs.registerCommand("diff", rt);

	cs.executeCommand("help");

#ifdef DEBUG
//	cs.executeCommand("plot");
	cs.executeCommand("diff");
	quit();
#endif
}

void Application::quit(void) {
	this->_exit = true;
}

void Application::loop(void) {
	std::string in, in_prev;
//	Runtime* tt = Runtime::getSingletonPtr();

	if (_exit != true) {
		int retCode;
		do {
			retCode = cs.readLine();
			// We can also change the prompt based on last return value:
			if (retCode == ret::Ok)
				cs.setGreeting(GREET);
			else
				cs.setGreeting(GREET);

			if (retCode == 1) {
				std::cout << "Received error code 1\n";
			} else if (retCode == 2) {
				std::cout << "Received error code 2\n";
			}
		} while (retCode != ret::Quit);
	} else {
//		quit();
	}

}

void Application::handle(std::string msg) {
	if (msg == "exit") {
		quit();
	} else if (msg.empty() || msg != "exit") {
		std::cout << "Wrong word!" << std::endl;
	}
}

void Application::kill(void) {
}

void Application::clear(void) {
}

void Application::go(void) {
	init();
	loop();
	clear();
	kill();
}

}
