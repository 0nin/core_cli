/*
 * Conv.h
 *
 *  Created on: Aug 25, 2016
 *      Author: caveman
 */

#ifndef CONV_HPP_
#define CONV_HPP_

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <random>
#include "Common.h"

namespace Conv {

extern bool datLine(std::string &str);
extern bool csvLine(std::string &str);

template<typename T1, typename T2>
bool dat2vec(const std::string &file, std::vector<std::pair<T1, T2>> &copy,
		size_t colX = 1, size_t colY = 2) {
	std::string line;
	std::string path = file;
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
#ifdef __MINGW32__
						x = std::atof(word.c_str());
#else
						x = std::stod(word);
#endif
						else
						break;
					xI = true;
				} else if (count == colY) {
					if (!word.empty())
#ifdef __MINGW32__
						x = std::atof(word.c_str());
#else
						x = std::stod(word);
#endif
						else
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

template<typename T1, typename T2>
bool dat2list(const std::string &file, std::list<std::vector<std::pair<T1, T2>>>&copy) {
	std::string line;
	std::vector<std::pair<T1, T2>> stroke;
	std::string path = file;
	std::ifstream datFile(path);
	std::stringstream tmp;
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
		dat2vec (file, stroke, x, y+1);
		if (!stroke.empty())
		copy.push_back (stroke);
		stroke.clear();
	}

	datFile.close();
	return true;
}

extern bool csv2dat(const std::string &in, const std::string &out);
extern bool dat2csv(const std::string &in, const std::string &out);
extern bool text2vec(const std::string &file, std::vector<std::string> &copy);

template<typename T1, typename T2>
bool vec2dat(const std::vector<std::pair<T1, T2>> &data,
		const std::string &out) {
	std::ofstream write;
	write.open(out);
	if (write.is_open()) {
		for (auto it = data.begin(); it != data.end(); ++it) {
			write << it->first << " " << it->second << std::endl;
		}
		write.close();
	} else
		return false;

#ifdef NDEBUG
	std::cout << "__X__" << " " << "__DATA__" << std::endl;
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}
#endif

	return true;
}

template<typename T1, typename T2>
bool list2dat(const std::list<std::vector<std::pair<T1, T2>>>&dataList,
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
				tmp << it->at(i).first << " " << it->at(i).second << " ";
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

template<typename T1, typename T2>
bool list2csv(const std::list<std::vector<std::pair<T1, T2>>>&dataList,
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
				tmp << it->at(i).first << "," << it->at(i).second << ",";
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
	}
	else
	return false;
	file.clear();

	return true;
}

}
#endif /* CONV_HPP_ */
