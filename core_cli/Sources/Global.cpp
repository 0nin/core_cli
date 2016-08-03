/*
 * Global.cpp
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#include "Global.h"

#include "Application.hpp"
//#include "Library.hpp"
//#include "Runtime.hpp"
//#include "Console.hpp"
#include "Exception.hpp"
//#include "Gnuplot.hpp"
#include "PathList.hpp"

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>

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

//namespace Core {

template<class T>
bool list2dat(const std::list<std::vector<std::pair<T, T>>>&dataList,
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
void flux(const std::vector<std::pair<T, T>> &data,
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

template<class T>
bool atos(T real, std::string &str) {
//	bool result = true;
//	std::ostringstream strs;
//	strs << real;
//	str = strs.str();
//	if (str.empty())
//		return false;

	str = std::to_string(real);
	if (str.empty())
		return false;

	return true;
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

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
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

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == ',' && wordBegin)
			*it = ' ';
		if (isDigit(*it))
			continue;
		else
			*it = ' ';
	}

	return true;
}

bool copyText(const std::string &file, std::vector<std::string> &copy) {
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
		return false;
	}

//	return ret::Ok;
	return true;
}

bool copyData(const std::string &file,
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
		return false;
	}

	datFile.close();
	return true;
}

template<class T>
bool copyColumn(const std::string &file, std::vector<double> &copy,
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
		return false;
	}

	datFile.close();
//	return ret::Ok;
	return true;
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

	for (std::vector<std::string>::iterator it = copy.begin(); it != copy.end(); ++it) {
		if (!fixLine(*it))
			return 1;
	}

	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (std::vector<std::string>::const_iterator it = copy.begin(); it != copy.end(); ++it) {
			write << *it << std::endl;
		}
		write.close();
	}

	copy.clear();

	return true;
}

bool dat2cvs(const std::string &file, const std::string &out) {
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

	for (std::vector<std::string>::iterator it = copy.begin(); it != copy.end(); ++it) {
		if (!fixLine(*it))
			return 1;
	}

	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (std::vector<std::string>::const_iterator it = copy.begin(); it != copy.end(); ++it) {
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




//}
