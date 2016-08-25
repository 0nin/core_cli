/*
 * Conv.h
 *
 *  Created on: Aug 25, 2016
 *      Author: caveman
 */

#ifndef CONV_H_
#define CONV_H_

#include "Common.h"

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <random>

//template<typename T1, typename T2>
//extern bool dat2vec(const std::string &file,
//		std::vector<std::pair<T1, T2>> &copy, size_t colX, size_t colY);
template<typename T1, typename T2>
bool dat2vec(const std::string &file, std::vector<std::pair<T1, T2>> &copy,
		size_t colX, size_t colY) {
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
						x = std::stod(word);
					else
						break;
					xI = true;
				} else if (count == colY) {
					if (!word.empty())
						y = std::stod(word);
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

//template<typename T1, typename T2>
//extern bool dat2list(const std::string &file,
//		std::list<std::vector<std::pair<T1, T2>>>&copy);
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


#endif /* CONV_H_ */
