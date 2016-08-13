/*
 * Global.h
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include "Common.h"

template<class T>
extern std::string atos(T real);
extern std::string rand(size_t range);
extern bool fileExist (const std::string &name);
template<class T1, class T2>
extern void printVec(const std::vector<std::pair<T1, T2>>&dataVec);
extern void printList(const std::list<std::vector<std::pair<double, double>>>&dataList);


extern bool csv2dat(const std::string &file, const std::string &out);
extern bool dat2csv(const std::string &file, const std::string &out);
extern bool isDigit(char ch);
extern bool datLine(std::string &str);

extern bool text2vec(const std::string &file, std::vector<std::string> &copy);
extern bool dat2vec(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX, size_t colY);
extern bool dat2list(const std::string &file,
		std::list<std::vector<std::pair<double, double>>>&copy);
template<class T>
extern bool vec2dat(const std::vector<std::pair<T, T>> &data,
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
//extern double getTauVec(const std::vector<std::pair<double, double>>&dataVec);
//extern double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList);

extern double getTauVec(const std::vector<std::pair<double, double>>&dataVec);
extern double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList);

#endif /* GLOBAL_HPP_ */
