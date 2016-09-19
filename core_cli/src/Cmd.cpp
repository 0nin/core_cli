/*
 * Cmd.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#include "Cmd.hpp"

#include <cstdio>
#include <sstream>
#include <fstream>
#include <math.h>

#include "Console.hpp"
#include "Conv.h"
#include "Global.h"
#include "Gnuplot.hpp"
#include "PathList.hpp"

using namespace Conv;
//using namespace Core;
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

#define _USE_MATH_DEFINES

//Readline commands

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
	double num1, num2;
//	double num1 = std::stod(input[1]), num2 = std::stod(input[3]);
#ifdef __MINGW32__
	num1 = std::atof(input[1].c_str()), num2 = std::atof(input[3].c_str());
#else
	num1 = std::stod(input[1]), num2 = std::stod(input[3]);
#endif

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

//	std::string line;
	std::string path;
	std::string out = input[1] + std::string(".csv");
//	std::st
	Core::PathList::getSingletonPtr()->getPath(input[1], path);
	csv2dat(path, input[2]);

	return ret::Ok;
}

unsigned tauCmd(const std::vector<std::string> &) {
//	std::list<std::vector<std::pair<double, double>>>tmp;
//	std::vector<std::pair<double, double>> tmp;
	std::list<std::vector<std::pair<double, double>>>dat;
	std::list<std::vector<std::pair<double, double>>>diff;
	std::list<std::vector<std::pair<double, double>>>diffNorm;

#ifdef _WIN32
	std::string file = "V:/cableCheck.dat";
#else
	std::string file = "cableCheck.dat";
#endif

	dat2list(file, dat);
	fluxList(dat, diff);
	normListNoRet(diff);
	list2dat(diff, "./tmp/norm.dat");
	list2csv(diff, "./tmp/norm.csv");
	for (auto it = diff.begin(); it != diff.end(); ++it ) {
		std::cout <<"NEXT DIE: " << std::endl;
		getTauVec (*it);
	}

	return ret::Ok;
}

unsigned plotCmd(const std::vector<std::string> &input) {
	static Core::Gnuplot gp, gp1;

#ifdef _WIN32
	std::string file = "V:/cableCheck.dat";
#else
	std::string file = "cableCheck.dat";
#endif
	std::vector<std::pair<double, double>> tmp;
	std::list<std::vector<std::pair<double, double>>>data;
	std::vector<std::pair<double, double>> diff;

	for (double x = -3.14f; x < 3.14f; x += 0.01f) {
		tmp.push_back(std::make_pair(x, sin(x)));
	}
	flux(tmp, diff);
	data.push_back(tmp);
	data.push_back(diff);
	gp1.plot(data);
	gp.plotDat("plot.dat", 1);
	return ret::Ok;
}
