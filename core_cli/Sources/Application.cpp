#include "Application.hpp"

#include "Library.hpp"
#include "Runtime.hpp"
#include "Console.hpp"
#include "Exception.hpp"
#include "Gnuplot.hpp"
#include "PathList.hpp"

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

bool isDigit(char ch)
{
	const char digits[] = "0123456789.\t\n ";
	size_t N = sizeof(digits) / sizeof(char);

	for (size_t i = 0; i < N; i++)
	{
		if (ch == digits[i])
			return true;
	}
	return false;
}

bool fixLine(std::string &str)
{
	bool result = true;
	if (str[0] == '#')
		return true;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == ',')
			*it = ' ';
		if (isDigit(*it))
			continue;
		else
//			return false;
			*it = ' ';
	}

	return result;
}

unsigned csv2dat(const std::vector<std::string> &input)
{
	if (input.size() != 2)
	{
		// The first element of the input array is always the name of the
		// command as registered in the console.
		std::cout << "Usage: " << input[0] << " name of file.csv\n";
		// We can return an arbitrary error code, which we can catch later
		// as Console will return it.
		return 1;
	}

	std::string line;
	std::string path;
	Core::PathList::getSingletonPtr()->getPath(input[1], path);
	std::ifstream csvFile(path);
	std::vector<std::string> copy;

	if (csvFile.is_open())
	{
		while (getline(csvFile, line))
		{
			copy.push_back(line);
		}
		csvFile.close();
		line.clear();
	}
	else
	{
		std::cerr << "I can't open to" + input[1] << std::endl;
	}

	for (auto it = copy.begin(); it != copy.end(); ++it)
	{
		if (!fixLine(*it))
			return 1;
	}

	std::ofstream file;
	file.open(input[1] + ".dat");
	if (file.is_open())
	{
		for (auto it = copy.begin(); it != copy.end(); ++it)
		{
			file << *it << std::endl;
		}
		file.close();
	}

	copy.clear();

	return ret::Ok;
}

unsigned plot(const std::vector<std::string> &input)
{
	Gnuplot plot;

	std::stringstream tmp;
	for (float i = -3.14f / 2.0f; i < 3.14f / 2.0f; i += 0.01)
	{
		tmp << i;
		tmp << ", ";
		tmp << std::abs(std::sin(i));
		tmp << ", ";
		tmp << 2 * std::sin(i) * std::cos(i);
		tmp << "\n";
	}

	std::ofstream file;
//	{
	file.open("plot.dat");
	if (file.is_open())
	{
		file << tmp.str();
		file.close();
	}
	tmp.clear();
//	}

	std::string path;
	if (!Core::PathList::getSingletonPtr()->getPath("plot.csv", path)){
//		std::cerr << ""
		return 1;
	}

	plot << "set grid";

	plot << "plot '" + path + "' using 1:2 with points";
	plot << "replot '" + path + "' using 1:3 with points";
	plot << "replot '" + path + "' using 1:4 with points";
	plot << "replot '" + path + "' using 1:5 with points";
//	plot << "replot 'plot.csv' using 1:3 with points";

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
		cs("(core)")
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
	cs.registerCommand("csv2dat", csv2dat);

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
