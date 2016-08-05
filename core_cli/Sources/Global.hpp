/*
 * Global.h
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

//#undef DEBUG

#include "Common.h"

template<class T0>
extern std::string atos(T0 real);
extern bool csv2dat(const std::string &file, const std::string &out);
extern bool dat2csv(const std::string &file, const std::string &out);
extern bool isDigit(char ch);
extern bool datLine(std::string &str);

extern bool copyText(const std::string &file, std::vector<std::string> &copy);
extern bool copy2vec(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX, size_t colY);
extern bool copy2list(const std::string &file,
		std::list<std::vector<std::pair<double, double>>>&copy);
template<class T>
extern bool vec2dat(const std::vector<std::pair<T, T>> &data,
		const std::string &out);
//template<class T1>
extern bool list2dat(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &out);
extern bool list2csv(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &out);
//template<class Temp>
extern void flux(const std::vector<std::pair<double, double>> &data,
		std::vector<std::pair<double, double>> &diff);
extern void fluxList(const std::list<std::vector<std::pair<double, double>>> &data,
		std::list<std::vector<std::pair<double, double>>> &diff);
//template<class T>
//extern void plotList(const std::string &name,
//		const std::list<std::vector<std::pair<T, T>>>&dataList);

#endif /* GLOBAL_HPP_ */
