/*
 * Global.h
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include "Common.h"
//#include "Conv.h"

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <random>

template<typename T>
extern std::string atos(T real);
extern std::string rand(size_t range);
extern bool fileExist (const std::string &name);
extern bool isDigit(char ch);


//template<typename T1, typename T2>
//extern void printVec(const std::vector<std::pair<T1, T2>>&dataVec);
//template<typename T1, typename T2>
//extern void printList(const std::list<std::vector<std::pair<T1, T2>>>&dataList);
template<typename T1, typename T2>
void printVec(const std::vector<std::pair<T1, T2>>&dataVec) {
	typename std::vector<std::pair<T1, T2>>::const_iterator DataVecCIt;
	std::cout << "VecLength: " << dataVec.size() << std::endl;
	for (auto it = dataVec.begin(); it != dataVec.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}

template<typename T1, typename T2>
void printList(const std::list<std::vector<std::pair<T1, T2>>>&dataList) {
	size_t maxSize = 0;
	typename std::list<std::vector<std::pair<double, double>>>::const_iterator DataListCIt;

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


extern bool datLine(std::string &str);
extern bool csv2dat(const std::string &in, const std::string &out);
extern bool dat2csv(const std::string &in, const std::string &out);

extern bool text2vec(const std::string &file, std::vector<std::string> &copy);

extern bool vec2dat(const std::vector<std::pair<double, double>> &data,
		const std::string &out);
extern bool list2dat(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &out);
extern bool list2csv(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &out);
extern void flux(const std::vector<std::pair<double, double>> &data,
		std::vector<std::pair<double, double>> &diff);
extern void fluxList(const std::list<std::vector<std::pair<double, double>>>&data,
std::list<std::vector<std::pair<double, double>>> &diff);


extern bool plotList(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &name);

extern bool normVec(const std::vector<std::pair<double, double>>&inData,
		std::vector<std::pair<double, double>>&outData);
extern bool normList(const std::list<std::vector<std::pair<double, double>>>&inData,
std::list<std::vector<std::pair<double, double>>>&outData);
extern bool normVecNoRet(std::vector<std::pair<double, double>>&inData);
extern bool normListNoRet(std::list<std::vector<std::pair<double, double>>>&inData);
extern double getTauVec(const std::vector<std::pair<double, double>>&dataVec);
extern double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList);

#endif /* GLOBAL_HPP_ */
