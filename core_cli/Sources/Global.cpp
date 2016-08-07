/*
 * Global.cpp
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#include "Global.hpp"

#include "Application.hpp"
#include "Exception.hpp"

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace Core;
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

const char digits[] = "0123456789.\t\n";

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

double getDummy() {
#ifdef _WIN32
	return 0.0f;
#else
	return 0.0f;
#endif
}

template<class T>
std::string atos(T real) {
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
	if (str.empty())
		return std::string("");

//	std::string str = std::to_string(real);
//	if (str.empty())
//		return std::string("");

	return str;
}

void printList(const std::list<std::vector<std::pair<double, double>>>&dataList) {
	size_t maxSize = 0;
	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	std::cout << "MaxSize: " << maxSize << std::endl;
	std::cout << "ListLength: " << dataList.size() << std::endl;

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i) {
//				if (it == dataList.begin()) {
//					std::cout << it->at(i).first << " " << it->at(i).second << " ";
//				}
//				else {
//					std::cout << it->at(i).second << " ";
//				}
				std::cout << it->at(i).first << " " << it->at(i).second << " ";
			}
		}
		std::cout << std::endl;
//		tmp << std::endl;
//		file += tmp.str();
//		tmp.str( std::string() );
//		tmp.clear();
	}

}

//template<class T1>
bool list2dat(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &out) {
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

bool list2csv(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &out) {
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

//template<class Temp>
void flux(const std::vector<std::pair<double, double>> &data,
		std::vector<std::pair<double, double>> &diff) {
	diff.clear();
	for (auto it = data.begin(); it != data.end() - 1; ++it) {
		double x = it->first;
		double y = it->second;
		double x1 = (it + 1)->first;
		double y1 = (it + 1)->second;

		diff.push_back(std::make_pair(x, (y1 - y) / (x1 - x)));
	}

}

//template<class Temp>
void fluxList(const std::list<std::vector<std::pair<double, double>>>&data,
std::list<std::vector<std::pair<double, double>>> &diff) {
	diff.clear();
	std::vector<std::pair<double, double>> tmp;
	for (auto it = data.begin(); it != data.end(); ++it) {
		flux(*it, tmp);
		diff.push_back(tmp);
		tmp.clear();
	}
}
//template<class T>
//bool atos(T real, std::string &str) {
////	bool result = true;
////	std::ostringstream strs;
////	strs << real;
////	str = strs.str();
////	if (str.empty())
////		return false;
//
//	str = std::to_string(real);
//	if (str.empty())
//		return false;
//
//	return true;
//}

bool isDigit(char ch) {
//	const char digits[] = "0123456789.\t\n ";
	size_t N = sizeof(digits) / sizeof(char);

	for (size_t i = 0; i < N; i++) {
		if (ch == digits[i])
			return true;
	}
	return false;
}

bool datLine(std::string &str) {
	if (str[0] == '#')
		return true;

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == ',')
			*it = ' ';
		else if (isDigit(*it))
			continue;
//		else
//			*it = ' ';
	}

	return true;
}

bool csvLine(std::string &str) {
	bool wordEnd = true;
	if (str[0] == '#')
		return true;

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == ' ' && wordEnd) {
			*it = ',';
			wordEnd = false;
		} else if (isDigit(*it)) {
			wordEnd = true;
			continue;
		} else {
//			*it = ' ';
		}
	}

	return true;
}

bool copyText(const std::string &file, std::vector<std::string> &copy) {
	std::string line;
	std::string path = file;
//	Core::PathList::getSingletonPtr()->getPath(file, path);
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

bool copy2vec(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX,
		size_t colY) {
	std::string line;
	std::string path = file;
//	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream datFile(path);
	std::stringstream tmp;
	double x = DUMMY, y = DUMMY;
	bool xI = false, yI = false;

	copy.clear();

	if (datFile.is_open()) {
		while (getline(datFile, line)) {
			xI = false;
			yI = false;
			if (line[0] == '#')
				continue;
			datLine(line);
			std::istringstream iss(line);
			size_t count = 0;
			while (iss) {
				std::string word;
				iss >> word;

				count++;
				if (count == colX) {
					if (!word.empty())
						x = std::stod(word);
					else
//						x = getDummy();
						break;
					xI = true;
				} else if (count == colY) {
					if (!word.empty())
						y = std::stod(word);
					else
//						y = getDummy();
						break;
					yI = true;
				} else if (xI && yI) {
					break;
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

bool copy2list(const std::string &file,
		std::list<std::vector<std::pair<double, double>>>&copy) {
	std::string line;
	std::vector<std::pair<double, double>> stroke;
	std::string path = file;
//	Core::PathList::getSingletonPtr()->getPath(file, path);
	std::ifstream datFile(path);
	std::stringstream tmp;
//	double x, y;
//	bool xI = false, yI = false;
	size_t x=1, y=1;
	size_t colX=1, colY=1;
	bool check = false;
	copy.clear();

	if (datFile.is_open()) {
		while (getline(datFile, line)) {
			if (line[0] == '#')
			continue;
			datLine(line);
			std::istringstream iss(line);
			size_t count = 0;
			while (iss) {
				std::string word;
				iss >> word;
				count++;
			}
			check = true;
			colY = count;
			colX = 1;
			if (check) break;
		}
		line.clear();
	} else {
		std::cerr << "I can't open to " + file << std::endl;
		return false;
	}

	for (y = colX; y<colY; y++) {
		copy2vec (file, stroke, x, y+1);
		if (!stroke.empty())
		copy.push_back (stroke);
		stroke.clear();
	}

	datFile.close();
	return true;
}

template<class T>
bool copy2column(const std::string &file, std::vector<double> &copy,
		size_t colXY) {
	std::string line;
	std::string path = file;
//	Core::PathList::getSingletonPtr()->getPath(file, path);
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
			datLine(line);
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
	std::string path = file;
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

	for (std::vector<std::string>::iterator it = copy.begin(); it != copy.end();
			++it) {
		if (!datLine(*it))
			return 1;
	}

	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (std::vector<std::string>::const_iterator it = copy.begin();
				it != copy.end(); ++it) {
			write << *it << std::endl;
		}
		write.close();
	}

	copy.clear();

	return true;
}

bool dat2csv(const std::string &file, const std::string &out) {
	std::string line;
	std::string path = file;
//	Core::PathList::getSingletonPtr()->getPath(file, path);
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

	for (std::vector<std::string>::iterator it = copy.begin(); it != copy.end();
			++it) {
		if (!csvLine(*it))
			return 1;
	}

	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (std::vector<std::string>::const_iterator it = copy.begin();
				it != copy.end(); ++it) {
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
