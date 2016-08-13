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

#include <cstdio>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace Core;
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

//	std::string line;
	std::string path;
	std::string out = input[1] + std::string(".csv");
//	std::st
	Core::PathList::getSingletonPtr()->getPath(input[1], path);
	dat2csv(path, input[2]);

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
	for (auto it = diff.begin(); it != diff.end(); ++it ){
		std::cout <<"NEXT DIE: " << std::endl;
		getTauVec (*it);
	}

	return ret::Ok;
}

unsigned plotCmd(const std::vector<std::string> &input) {
	Gnuplot gp, gp1, gp2;

#ifdef _WIN32
	std::string file = "V:/cableCheck.dat";
#else
	std::string file = "cableCheck.dat";
#endif
//	std::list<std::vector<std::pair<double, double>>>tmp;
//	std::list<std::vector<std::pair<double, double>>>dat;
//	std::list<std::vector<std::pair<double, double>>>diff;
//
//	dat2list(file, dat);
//	list2dat(dat, "out.dat");
//	dat2csv("out.dat", "out.csv");
//
//	std::vector<std::pair<double, double>> tmpflux;
//	for (auto it = dat.begin(); it != dat.end(); ++it) {
//		tmp.push_back(*it);
//		if (!tmp.empty()) {
//			flux(*it, tmpflux);
//			tmp.push_back(tmpflux);
//			gp.plot(tmp, "");
//			tmp.clear();
//			tmpflux.clear();
//		}
//	}

//	gp.plot();
#ifdef DEBUG
//	printList(dat);
#endif
//	fluxList(dat, diff);
//
//	gp.close();
//	dat.clear();
//	diff.clear();
	std::list<std::vector<std::pair<double, double>>> data;
	std::vector<std::pair<double, double>> tmp;
	for (double x = -M_PI; x < M_PI; x+=0.01f) {
		tmp.push_back(std::make_pair(x, sin(x)));
	}
	data.push_back(tmp);
	gp2.plot(data);
	gp.plotDat("cableCheck.dat", 4);
	gp1.plotDat("plot.dat", 4);
//	gp.close();
	return ret::Ok;
}
