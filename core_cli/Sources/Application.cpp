#include "Application.hpp"

#include "Library.hpp"
#include "Runtime.hpp"
#include "Console.hpp"
#include "Exception.hpp"
#include "PathList.hpp"
#include "Gnuplot.hpp"
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>

#include "Cmd.hpp"
#include "Global.hpp"

#define GREET "(core)"


namespace Core {


namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

Application::Application(const std::string &path, const std::string &configFile) :
		cs("(core)") {
	_exit = false;
	this->path = path;
	this->config = configFile;
}

Application::~Application(void) {
// empty
}

void Application::init(void) {
	Library::getSingletonPtr()->loadConfigFile("core.cfg");

	cs.registerCommand("info", infoCmd);
	cs.registerCommand("calc", calcCmd);
	cs.registerCommand("plot", plotCmd);
	cs.registerCommand("csv2dat", csv2datCmd);
//	cs.registerCommand("diff", rtCmd);

	cs.executeCommand("help");

#ifdef DEBUG
	cs.executeCommand("plot");
//	cs.executeCommand("diff");
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

void Application::handle(const std::string &msg) {
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
