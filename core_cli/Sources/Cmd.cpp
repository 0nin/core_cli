/*
 * Cmd.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#include "Cmd.hpp"
#include "Gnuplot.hpp"
#include "Global.hpp"
#include "Console.hpp"
#include "PathList.hpp"

using namespace Core;
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

//Readline commands
unsigned plotCmd(const std::vector<std::string> &input) {
	Gnuplot gp;

//	std::stringstream tmp;
//	for (float i = -3.14f / 2.0f; i < 3.14f / 2.0f; i += 0.01) {
//		tmp << i;
//		tmp << ", ";
//		tmp << std::abs(std::sin(i));
//		tmp << ", ";
//		tmp << 2 * std::sin(i) * std::cos(i);
//		tmp << "\n";
//	}
//
//	std::ofstream file;
//	file.open("plot.dat");
//	if (file.is_open()) {
//		file << tmp.str();
//		file.close();
//	}
//	tmp.clear();

//	std::string path;
//	if (!Core::PathList::getSingletonPtr()->getPath("cableCheck.dat", path)) {
//		return 1;
//	}

//	path = std::string("V:\\") + "cableCheck2211.dat";
//	gp << "set term wxt 0";
//	gp << "set grid";
//
//	gp << "plot '" + path + "' using 1:2 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:3 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:4 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:5 with linespoints pt 7 ps 0.5";
//
//	path = std::string("V:\\") + "cableCheck1122.dat";
//
//	gp << "set term wxt 1";
//	gp << "set grid";
//
//	gp << "plot '" + path + "' using 1:2 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:3 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:4 with linespoints pt 7 ps 0.5";
//	gp << "replot '" + path + "' using 1:5 with linespoints pt 7 ps 0.5";
//
//	gp << "end";

	return ret::Ok;
}

// In this command we implement a basic calculator
unsigned calcCmd(const std::vector<std::string> & input) {
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

unsigned infoCmd(const std::vector<std::string> &) {
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

unsigned csv2datCmd(const std::vector<std::string> &input) {
	if (input.size() != 3) {
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
	file.open(input[2]);
	if (file.is_open()) {
		for (auto it = copy.begin(); it != copy.end(); ++it) {
			file << *it << std::endl;
		}
		file.close();
	}

	copy.clear();

	return ret::Ok;
}
