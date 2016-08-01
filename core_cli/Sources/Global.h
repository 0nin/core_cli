/*
 * Global.h
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

//#undef DEBUG

#include <string>
#include <vector>
#include <list>

unsigned info(const std::vector<std::string> &);
bool isDigit(char ch);
bool fixLine(std::string &str);
unsigned copy(const std::string &file, std::vector<std::string> &copy);
unsigned copy(const std::string &file,
		std::vector<std::pair<double, double>> &copy, size_t colX, size_t colY);
bool csv2datOut(const std::string &file, const std::string &out);
template<class T>
bool vec2dat(const std::vector<std::pair<T, T>> &data, const std::string &out);
template<class T>
bool vec2dat(const std::list<std::vector<std::pair<T, T>>>&dataList, const std::string &out, const std::string &header);
template<class T>
bool list2dat(const std::list<std::vector<T>>&dataList, const std::string &out, const std::string &header);
template<class T>
void diff(const std::vector<std::pair<T, T>> &data,
		std::vector<std::pair<T, T>> &diff);
unsigned rt(const std::vector<std::string> &);
unsigned plot(const std::vector<std::string> &input);
unsigned calc(const std::vector<std::string> & input);
unsigned csv2dat(const std::vector<std::string> &input);


#endif /* GLOBAL_H_ */
