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
#include <algorithm>
#include <iterator>
#include <list>

#define GREET "(core)"

namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

int main(int argc, char *args[]) {
	try {
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e) {
		Core::Exception::die(e.getDescription(), "error.log");
		return 1;
	}
	return 0;
}

unsigned info(const std::vector<std::string> &) {
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

bool isDigit(char ch) {
	const char digits[] = "0123456789.\t\n ";
	size_t N = sizeof(digits) / sizeof(char);

	for (size_t i = 0; i < N; i++) {
		if (ch == digits[i])
			return true;
	}
	return false;
}

bool fixLine(std::string &str) {
	if (str[0] == '#')
		return true;

	for (auto it = str.begin(); it != str.end(); ++it) {
		if (*it == ',')
			*it = ' ';
		if (isDigit(*it))
			continue;
		else
			*it = ' ';
	}

	return true;
}

unsigned copy(const std::string &file, std::vector<std::string> &copy) {
	std::string line;
	std::string path;
	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream csvFile(path);

	copy.clear();

	if (csvFile.is_open()) {
		while (getline(csvFile, line)) {
			copy.push_back(line);
		}
		csvFile.close();
		line.clear();
	} else {
		std::cerr << "I can't open to " + file << std::endl;
		return 1;
	}

	return ret::Ok;
}

unsigned copy(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX,
		size_t colY) {
	std::string line;
	std::string path;
	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream datFile(path);
	std::stringstream tmp;
	double x, y;
	bool xI = false, yI = false;

	copy.clear();

	if (datFile.is_open()) {
		while (getline(datFile, line)) {
			xI = false;
			yI = false;
			if (line[0] == '#')
				continue;
			fixLine(line);
			std::istringstream iss(line);
			size_t count = 0;
			while (iss) {
				std::string word;
				iss >> word;

				count++;
				if (count == colX) {
					x = std::stod(word);
					xI = true;
				} else if (count == colY) {
					y = std::stod(word);
					yI = true;
				} else {
					//do nothing
				}
			}
			if (xI && yI)
				copy.push_back(std::make_pair(x, y));
		}
		line.clear();
	} else {
		std::cerr << "I can't open to " + file << std::endl;
		return 1;
	}

//#ifdef DEBUG
//	std::cout << "__X__" << "  " << "__Y__" << std::endl;
//	for (auto it = copy.begin(); it != copy.end(); ++it) {
//		std::cout << it->first << "  " << it->second << std::endl;
//	}
//#endif

	datFile.close();
	return ret::Ok;
}

bool csv2dat(const std::string &file, const std::string &out) {
	std::string line;
	std::string path;
	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream csvFile(path);
	std::vector<std::string> copy;

	if (csvFile.is_open()) {
		while (getline(csvFile, line)) {
			copy.push_back(line);
		}
		csvFile.close();
		line.clear();
	} else {
		std::cerr << "I can't open to" + file << std::endl;
	}

	for (auto it = copy.begin(); it != copy.end(); ++it) {
		if (!fixLine(*it))
			return 1;
	}

	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (auto it = copy.begin(); it != copy.end(); ++it) {
			write << *it << std::endl;
		}
		write.close();
	}

	copy.clear();

	return true;
}

template<class T>
bool vec2dat(const std::vector<std::pair<T, T>> &data, const std::string &out) {
	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (auto it = data.begin(); it != data.end(); ++it) {
			write << it->first << "  " << it->second << std::endl;
		}
		write.close();
	} else
		return false;

#ifdef DEBUG
	std::cout << "__X__" << "  " << "__DATA__" << std::endl;
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
#endif

	return true;
}

template<class T>
bool vec2dat(const std::list<std::vector<std::pair<T, T>>>&dataList, const std::string &out) {
//	std::string line;
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	size_t maxSize = 0;
	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() >= i) tmp << it->at(i).first << "  " << it->at(i).second << "  ";
		}
		tmp << std::endl;
		file += tmp.str();
		tmp.str( std::string() );
		tmp.clear();
	}

	write.open(out);
	if (write.is_open()) {
		write << file;
		write.close();
	} else
	return false;
	file.clear();

//#ifdef DEBUG
//	std::cout << "__X__" << "  " << "__DATA__" << std::endl;
//	for (auto it = data.begin(); it != data.end(); ++it) {
//		std::cout << it->first << "  " << it->second << std::endl;
//	}
//#endif
	return true;
}

unsigned conv(const std::vector<std::string> &input) {
	if (input.size() != 2) {
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

	if (csvFile.is_open()) {
		while (getline(csvFile, line)) {
			copy.push_back(line);
		}
		csvFile.close();
		line.clear();
	} else {
		std::cerr << "I can't open to" + input[1] << std::endl;
	}

	for (auto it = copy.begin(); it != copy.end(); ++it) {
		if (!fixLine(*it))
			return 1;
	}

	std::ofstream file;
	file.open(input[1] + ".dat");
	if (file.is_open()) {
		for (auto it = copy.begin(); it != copy.end(); ++it) {
			file << *it << std::endl;
		}
		file.close();
	}

	copy.clear();

	return ret::Ok;
}

template<class T>
void diff(const std::vector<std::pair<T, T>> &data,
		std::vector<std::pair<T, T>> &diff) {
	diff.clear();
	for (auto it = data.begin(); it != data.end() - 1; ++it) {
		T x = it->first;
		T y = it->second;
		T x1 = (it + 1)->first;
		T y1 = (it + 1)->second;

		diff.push_back(std::make_pair(x, (y1 - y) / (x1 - x)));
	}

//#ifdef DEBUG
//	std::cout << "__X__" << "  " << "__DATA__" << std::endl;
//	for (auto it = data.begin(); it != data.end(); ++it) {
//		std::cout << it->first << "  " << it->second << std::endl;
//	}
//#endif
//
//#ifdef DEBUG
//	std::cout << "__X__" << "  " << "__DIFF__" << std::endl;
//	for (auto it = diff.begin(); it != diff.end(); ++it) {
//		std::cout << it->first << "  " << it->second << std::endl;
//	}
//#endif
}

unsigned rt(const std::vector<std::string> &) {
//	const std::string file = "plot.dat";
	csv2dat("plot.csv", "plot.dat");
	std::ofstream write;

	std::vector<std::pair<double, double>> data, data1, data2, data3, data4;
	std::vector<std::pair<double, double>> d2;
	std::vector<std::pair<double, double>> d3;

	copy("plot.dat", data1, 1, 2);
	diff(data1, d2);
	diff(d2, d3);
	vec2dat(d2, "diff2.dat");

	copy("plot.dat", data2, 1, 3);
	diff(data2, d2);
	vec2dat(d2, "diff3.dat");

	copy("plot.dat", data3, 1, 4);
	diff(data3, d2);
	vec2dat(d2, "diff4.dat");

	copy("plot.dat", data4, 1, 5);
	diff(data4, d2);
	vec2dat(d2, "diff5.dat");

	std::list<std::vector<std::pair<double, double>>>datList;
	datList.push_back(data1);
	datList.push_back(data2);
	datList.push_back(data3);
	datList.push_back(data4);

	vec2dat(datList, "plot2.dat");

//#ifdef DEBUG
//	std::cout << "__X__" << "  " << "__DIFF__" << std::endl;
//	for (auto it = dd.begin(); it != dd.end(); ++it)
//	{
//		std::cout << it->first << "  " << it->second << std::endl;
//	}
//#endif

	return ret::Ok;
}

unsigned plot(const std::vector<std::string> &input) {
	Gnuplot plot;

	std::stringstream tmp;
	for (float i = -3.14f / 2.0f; i < 3.14f / 2.0f; i += 0.01) {
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
	if (file.is_open()) {
		file << tmp.str();
		file.close();
	}
	tmp.clear();
//	}

	std::string path;
	if (!Core::PathList::getSingletonPtr()->getPath("normalized.dat", path)) {
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
unsigned calc(const std::vector<std::string> & input) {
	if (input.size() != 4) {
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
	switch (op) {
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

namespace Core {
//#define errorNULL throw Exception( "null pointer");

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
	cs.registerCommand("conv", conv);
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
