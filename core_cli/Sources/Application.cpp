#include "Application.hpp"

#include "Library.hpp"
#include "Runtime.hpp"
#include "Console.hpp"
#include "Exception.hpp"

#include "Gnuplot.hpp"

#include <sstream>
#include <fstream>
#include <cmath>

namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

int main(int argc, char *args[])
{
	try
	{
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e)
	{
		Core::Exception::die(e.getDescription(), "error.log");
		return 1;
	}
	return 0;
}

unsigned info(const std::vector<std::string> &)
{
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

unsigned plot(const std::vector<std::string> &input)
{
	Gnuplot plot;

	plot("set key left box");
	plot("set autoscale");
	plot("set samples 800");
//	plot("plot [-30:20] sin(x*20)*atan(x)");

//    plot("plot '-' using 1:2 with lines\n");
	//	plot(str.str());
	//	plot("e");

	if (input.size() < 2)
	{
		std::cout << "Empty stroke" << std::endl;
		return 1;
	}
	else if (input.size() > 3)
	{
		std::cout << "Too much parameters" << std::endl;
		return 1;

	}

//	std::stringstream str;
//	for (float i = -3.14f / 2.0f; i < 3.14f / 2.0f; i += 0.01)
//	{
//		str << i;
//		str << ", ";
//		str << std::abs(std::sin(i));
//		str << ", ";
//		str << 2 * std::sin(i) * std::cos(i);
//		str << "\n";
//	}
//
//	std::ofstream file;
//	file.open("plot.dat");
//	if (file.is_open())
//	{
//		file << str.str();
//		file.close();
//	}
//
//	plot("plot 'plot.dat' using 1:2 with lines");
//	plot("replot 'plot.dat' using 1:3 with lines");
//
//	str.clear();
	std::string ans = std::string("plot") + input.at(1) + input.at(2);
	plot(ans);

	return ret::Ok;
}

// In this command we implement a basic calculator
unsigned calc(const std::vector<std::string> & input)
{
	if (input.size() != 4)
	{
		// The first element of the input array is always the name of the
		// command as registered in the console.
		std::cout << "Usage: " << input[0] << " num1 operator num2\n";
		// We can return an arbitrary error code, which we can catch later
		// as Console will return it.
		return 1;
	}
	double num1 = std::stod(input[1]), num2 = std::stod(input[3]);

	char op = input[2][0];

	double result;
	switch (op)
	{
	case '*':
		result = num1 * num2;
		break;
	case '+':
		result = num1 + num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	default:
		std::cout << "The inserted operator is not supported\n";
		// Again, we can return an arbitrary error code to catch it later.
		return 2;
	}
	std::cout << "Result: " << result << '\n';
	return 0;
}

namespace Core
{
#define errorNULL throw Exception( "null pointer");

Application::Application(std::string path, std::string configFile) :
		cs(">> ")
{
	_exit = false;
	this->path = path;
	this->config = configFile;

}

Application::~Application(void)
{
	// empty
}

void Application::init(void)
{
	Library::getSingletonPtr()->loadConfigFile("config.conf");

	cs.registerCommand("info", info);
	cs.registerCommand("calc", calc);
	cs.registerCommand("plot", plot);

	cs.executeCommand("help");

#ifdef DEBUG
//	cs.executeCommand("plot");
//	quit();
#endif
}

void Application::quit(void)
{
	this->_exit = true;
}

void Application::loop(void)
{
	std::string in, in_prev;
//	Runtime* tt = Runtime::getSingletonPtr();

	if (_exit != true)
	{
		int retCode;
		do
		{
			retCode = cs.readLine();
			// We can also change the prompt based on last return value:
			if (retCode == ret::Ok)
				cs.setGreeting(">> ");
			else
				cs.setGreeting(">> ");

			if (retCode == 1)
			{
				std::cout << "Received error code 1\n";
			}
			else if (retCode == 2)
			{
				std::cout << "Received error code 2\n";
			}
		} while (retCode != ret::Quit);
	}
	else
	{
//		quit();
	}

}

void Application::handle(std::string msg)
{
	if (msg == "exit")
	{
		quit();
	}
	else if (msg.empty() || msg != "exit")
	{
		std::cout << "Wrong word!" << std::endl;
	}
}

void Application::kill(void)
{
}

void Application::clear(void)
{
}

void Application::go(void)
{
	init();
	loop();
	clear();
	kill();
}

}
