/*
 * Global.h
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <random>
#include "Common.h"

//template<typename T>
//extern std::string atos(T real);
template<typename T>
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

extern std::string rand(size_t range);
extern bool fileExist (const std::string &name);
extern bool isDigit(char ch);


template<typename T1, typename T2>
void printVec(const std::vector<std::pair<T1, T2>>&dataVec) {
	std::cout << "VecLength: " << dataVec.size() << std::endl;
	for (auto it = dataVec.begin(); it != dataVec.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}

template<typename T1, typename T2>
void printList(const std::list<std::vector<std::pair<T1, T2>>>&dataList) {
	size_t maxSize = 0;

	for (auto it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	std::cout << "MaxSize: " << maxSize << std::endl;
	std::cout << "ListLength: " << dataList.size() << std::endl;

	for (size_t i = 0; i < maxSize; i++) {
		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i) {
				std::cout << it->at(i).first << " " << it->at(i).second << " ";
			}
		}
		std::cout << std::endl;
	}
}


//extern bool datLine(std::string &str);
//extern bool csv2dat(const std::string &in, const std::string &out);
//extern bool dat2csv(const std::string &in, const std::string &out);

//extern bool text2vec(const std::string &file, std::vector<std::string> &copy);
//extern bool vec2dat(const std::vector<std::pair<double, double>> &data,
//		const std::string &out);


//extern bool list2dat(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &out);

//template<typename T1, typename T2>
//extern bool list2csv(const std::list<std::vector<std::pair<double, double>>>&dataList,

//const std::string &out);
//extern void flux(const std::vector<std::pair<double, double>> &data,
//		std::vector<std::pair<double, double>> &diff);

template<typename T1, typename T2>
void flux(const std::vector<std::pair<T1, T2>> &data,
		std::vector<std::pair<T1, T2>> &diff) {
	diff.clear();

	for (auto it = data.begin(); it != data.end() - 1; ++it) {
		T1 x = it->first;
		T2 y = it->second;
		T1 x1 = (it + 1)->first;
		T2 y1 = (it + 1)->second;

		diff.push_back(std::make_pair(x, (y1 - y) / (x1 - x)));
	}

}

template<typename T1, typename T2>
void fluxList(const std::list<std::vector<std::pair<T1, T2>>>&data,
std::list<std::vector<std::pair<T1, T2>>> &diff) {
	diff.clear();
	std::vector<std::pair<T1, T2>> tmp;

	for (auto it = data.begin(); it != data.end(); ++it) {
		flux(*it, tmp);
		diff.push_back(tmp);
		tmp.clear();
	}
}


template<typename T1, typename T2>
bool normVec(const std::vector<std::pair<T1, T2>>&inData,
		std::vector<std::pair<T1, T2>>&outData) {
	if (!outData.empty()) {
		outData.clear();
	}
	if (inData.empty())
		return false;

	for (auto jt = inData.begin(); jt != inData.end();
			++jt) {
		if (jt->second > 0) {
			outData.push_back(std::make_pair(jt->first, (double) 1.0));
		} else {
			outData.push_back(std::make_pair(jt->first, (double) 0.0));
		}
	}

	return true;
}

template<typename T1, typename T2>
bool normList(const std::list<std::vector<std::pair<T1, T2>>>&inData,
std::list<std::vector<std::pair<T1, T2>>>&outData) {
	if (!outData.empty()) {
		outData.clear();
	}
	if(inData.empty())
	return false;
	typedef std::vector<std::pair<T1, T2>> DataVec;

	DataVec tmp;

	for (auto it = inData.begin(); it != inData.end(); ++it) {
		normVec (*it, tmp);
		outData.push_back(tmp);
	}
	if (!tmp.empty()) {
		tmp.clear();
	}

	return true;
}

template<typename T1, typename T2>
bool normVecNoRet(std::vector<std::pair<T1, T2>>&inData) {
	if (inData.empty())
		return false;

	typedef std::vector<std::pair<T1, T2>> DataVec;
	DataVec tmp;

	for (auto jt = inData.begin(); jt != inData.end(); ++jt) {
		if (jt->second > 0) {
			jt->second = (float) 1.0;
		} else {
			jt->second = (float) 0.0;
		}
	}

	return true;
}

template<typename T1, typename T2>
bool normListNoRet(std::list<std::vector<std::pair<T1, T2>>>&inData) {
	if(inData.empty())
	return false;

	for (auto it = inData.begin(); it != inData.end(); ++it) {
		normVecNoRet (*it);
	}

	return true;
}

extern double getTauVec(const std::vector<std::pair<double, double>>&dataVec);
extern double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList);

#endif /* GLOBAL_H_ */
