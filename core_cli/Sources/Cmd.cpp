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

using namespace Core;
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

//Readline commands
unsigned plotCmd(const std::vector<std::string> &input) {
	Gnuplot gp;

#ifdef _WIN32
	std::string file = "V:/cableCheck.dat";
#else
	std::string file = "cableCheck.dat";
#endif
	std::list<std::vector<std::pair<double, double>>>tmp;
	std::list<std::vector<std::pair<double, double>>>dat;
	std::list<std::vector<std::pair<double, double>>>diff;

	copy2list(file, dat);
	list2dat(dat, "out.dat");
	dat2csv("out.dat", "out.csv");
//	std::vector<size_t> col;
//	col.push_back(2);
//	col.push_back(3);
//	col.push_back(4);
//	col.push_back(5);
//	gp.plotDat(file, col);
//	gp.plot(dat, "");
//	plotList(dat,"TITLE");
//	size_t i = 0;
	std::vector<std::pair<double, double>> tmpflux;
	for (auto it = dat.begin(); it != dat.end(); ++it) {
		tmp.push_back(*it);
		if (!tmp.empty()) {
			flux(*it, tmpflux);
			tmp.push_back(tmpflux);
			gp.plot(tmp, "");
			tmp.clear();
			tmpflux.clear();
		}

	}

//	gp.plot();
#ifdef DEBUG
	printList(dat);
#endif
	fluxList(dat, diff);

//	for (auto it = dat.begin(); it != dat.end(); ++it)
//	flux(*it, diff);
//	Gnuplot gp;
//	gp.plot(diff, "");
//	plotList(diff,"DIFF");

	gp.close();
	dat.clear();
	diff.clear();
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
		if (!datLine(*it))
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
