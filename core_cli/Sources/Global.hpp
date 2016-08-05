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

//#include <string>
//#include <vector>
//#include <list>

template<class T>
extern std::string atos(T real);
extern bool csv2dat(const std::string &file, const std::string &out);
extern bool isDigit(char ch);
extern bool fixLine(std::string &str);

extern bool copyText(const std::string &file, std::vector<std::string> &copy);
extern bool copyData(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX, size_t colY);
template<class T>
extern bool vec2dat(const std::vector<std::pair<T, T>> &data,
		const std::string &out);
template<class T>
extern bool list2dat(const std::list<std::vector<std::pair<T, T>>>&dataList, const std::string &out, const std::string &header);
template<class T>
void flux(const std::vector<std::pair<T, T>> &data,
		std::vector<std::pair<T, T>> &diff);
template<class T>
extern void plotList(const std::string &name,
		const std::list<std::vector<std::pair<T, T>>>&dataList);

#endif /* GLOBAL_HPP_ */
