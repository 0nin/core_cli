/*
 * Conv.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: caveman
 */

#include "Conv.hpp"

#include "Global.h"

//bool datLine(std::string &str);
//bool csvLine(std::string &str);

namespace Conv {

bool datLine(std::string &str) {
	if (str[0] == '#')
		return true;

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == ',')
			*it = ' ';
		else if (isDigit(*it))
			continue;
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
		}
	}

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

bool text2vec(const std::string &file, std::vector<std::string> &copy) {
	std::string line;
	std::string path = file;
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

	return true;
}


}
