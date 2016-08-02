/*
 * Global.cpp
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#include "Global.h"
#include "Common.h"
#include "Console.hpp"
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
//#include <gnuplot-iostream.h>

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

bool csvLine(std::string &str) {
	bool wordBegin = false;
	if (str[0] == '#')
		return true;

	for (auto it = str.begin(); it != str.end(); ++it) {
		if (*it == ',' && wordBegin)
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

	datFile.close();
	return ret::Ok;
}

template<class T>
unsigned copyCol(const std::string &file, std::vector<double> &copy,
		size_t colXY) {
	std::string line;
	std::string path;
	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream datFile(path);
	std::stringstream tmp;
//	double x, y;
	double xy;
	bool xyI = false;

	copy.clear();

	if (datFile.is_open()) {
		while (getline(datFile, line)) {
			xyI = false;
			if (line[0] == '#')
				continue;
			fixLine(line);
			std::istringstream iss(line);
			size_t count = 0;
			while (iss) {
				std::string word;
				iss >> word;

				count++;
				if (count == colXY) {
					xy = std::stod(word);
					xyI = true;
				} else {
					//do nothing
				}
			}
			if (xyI)
				copy.push_back(xy);
		}
		line.clear();
	} else {
		std::cerr << "I can't open to " + file << std::endl;
		return 1;
	}

	datFile.close();
	return ret::Ok;
}

bool csv2datOut(const std::string &file, const std::string &out) {
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

bool dat2cvsOut(const std::string &file, const std::string &out) {
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
bool vec2dat(const std::vector<std::pair<T, T>> &data, const std::string &out,
		const std::string &header = std::string("")) {
	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (auto it = data.begin(); it != data.end(); ++it) {
			write << it->first << " " << it->second << std::endl;
		}
		write.close();
	} else
		return false;

#ifdef DEBUG
	std::cout << "__X__" << " " << "__DATA__" << std::endl;
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}
#endif

	return true;
}

template<class T>
bool vec2dat(const std::list<std::vector<std::pair<T, T>>>&dataList,
const std::string &out,
const std::string &header) {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	size_t maxSize = 0;
	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i) {
				if (it == dataList.begin()) {
					tmp << it->at(i).first << " " << it->at(i).second << " ";
				}
				else {
					tmp << it->at(i).second << " ";
				}
			}
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

	return true;
}

template<class T>
bool vec2csv(const std::list<std::vector<std::pair<T, T>>>&dataList,
const std::string &out,
const std::string &header="") {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	size_t maxSize = 0;
	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i) {
				if (it == dataList.begin()) {
					tmp << it->at(i).first << "," << it->at(i).second << ",";
				}
				else {
					tmp << it->at(i).second << ",";
				}
			}
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

	return true;
}

template<class T>
bool list2dat(const std::list<std::vector<T>>&dataList, const std::string &out,
		const std::string &header) {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	size_t maxSize = 0;
	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize)
			maxSize = it->size();
	}

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i)
				tmp << it->at(i) << " ";
		}
		tmp << std::endl;
		file += tmp.str();
		tmp.str(std::string());
		tmp.clear();
	}

	write.open(out);
	if (write.is_open()) {
		write << header << std::endl;
		write << file;
		write.close();
	} else
		return false;
	file.clear();

	return true;
}

unsigned csv2dat(const std::vector<std::string> &input) {
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

}

unsigned rt(const std::vector<std::string> &) {
	csv2datOut("cable.csv", "cable.dat");
	std::ofstream write;

	std::vector<std::pair<double, double>> data;
	std::vector<std::pair<double, double>> diff1;
	std::list<std::vector<std::pair<double, double>>>datList;
//	std::list<std::vector<double>>writeList;

	copy("cable.dat", data, 1, 2);
	diff(data, diff1);
	datList.push_back(data);
	datList.push_back(diff1);

	copy("cable.dat", data, 1, 3);
	diff(data, diff1);
	datList.push_back(data);
	datList.push_back(diff1);

	copy("cable.dat", data, 1, 4);
	diff(data, diff1);
	datList.push_back(data);
	datList.push_back(diff1);

	copy("cable.dat", data, 1, 5);
	diff(data, diff1);
	datList.push_back(data);
	datList.push_back(diff1);

	vec2dat(datList, "cable.dat", "");

	return ret::Ok;
}

//template <class T>
//void plotList(const std::string &name,
//    const std::list<std::vector<std::pair<T, T>>>&dataList) {
////  Gnuplot gp;
//
//  FILE* gnuplotpipe = popen(GNUPLOT_NAME, "w");
//  if (!gnuplotpipe) {
//    std::cerr << ("Gnuplot not found !");
//  }
//  std::stringstream tmp;
//  std::string fileName = name+".dat";
//  std::string path;
//  path = "/tmp/" + fileName;
////  path = fileName;
//  list2dat(dataList, path);
//
////  gp << "set grid";
//  fprintf (gnuplotpipe, "set grid \n");
////  fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());
//
//  ML_FOR_ACTIVE_DIES(die) {
//    if (die == 1) {
//      tmp << "plot 'plot.csv' using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5\n";
//    }
//    else {
//      tmp << "replot 'plot.csv' using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5\n";
//    }
//
//    fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());
//  }
//
//  fflush (gnuplotpipe); // flush needed to start render
//  pclose (gnuplotpipe);
//  tmp.str( std::string() );
//  tmp.clear();
//
////  return ret::Ok;
//}

template<class T>
void plotList(const std::string &name,
		const std::list<std::vector<std::pair<T, T>>>&dataList) {
//  Gnuplot gp;

	FILE* gnuplotpipe = popen(GNUPLOT_NAME, "w");
	if (!gnuplotpipe) {
		std::cerr << ("Gnuplot not found !");
	}
	std::stringstream tmp;
	std::string fileName = name+".dat";
	std::string path;
	path = "/tmp/" + fileName;
//  path = fileName;
	list2dat(dataList, path);

//  gp << "set grid";
	fprintf (gnuplotpipe, "set grid \n");
//  fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());

//	ML_FOR_ACTIVE_DIES(die) {
	for (size_t die = 1; die != 4; ++die) {
		if (die == 1) {
			tmp << "plot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5\n";
		}
		else {
			tmp << "replot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5\n";
		}

		fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());
	}

	fflush (gnuplotpipe); // flush needed to start render
	pclose (gnuplotpipe);
	tmp.str( std::string() );
	tmp.clear();

//  return ret::Ok;
}

unsigned plot(const std::vector<std::string> &input) {
	Core::Gnuplot gp;

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


	std::string path;
	if (!Core::PathList::getSingletonPtr()->getPath("cableCheck.dat", path)) {
//		std::cerr << ""
		return 1;
	}

	path = std::string("V:\\") + "cableCheck2211.dat";
	gp << "set term wxt 0";
	gp << "set grid";

	gp << "plot '" + path + "' using 1:2 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:3 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:4 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:5 with linespoints pt 7 ps 0.5";

	path = std::string("V:\\") + "cableCheck1122.dat";

	gp << "set term wxt 1";
	gp << "set grid";

	gp << "plot '" + path + "' using 1:2 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:3 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:4 with linespoints pt 7 ps 0.5";
	gp << "replot '" + path + "' using 1:5 with linespoints pt 7 ps 0.5";

	gp << "end";


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
