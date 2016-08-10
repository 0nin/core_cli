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

//int main(int argc, char *args[]) {
int main() {
	try {
//		Core::Application* app = new Core::Application("path.sc", "config.sc");
		Core::Application* app = new Core::Application("path.cfg", "core.cfg");
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

template<class T1, class T2>
void printVec(const std::vector<std::pair<T1, T2>>&dataVec) {
	typename std::vector<std::pair<T1, T2>>::const_iterator DataVecCIt;
	std::cout << "VecLength: " << dataVec.size() << std::endl;
	for (auto it = dataVec.begin(); it != dataVec.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}

void printList(const std::list<std::vector<std::pair<double, double>>>&dataList) {
	size_t maxSize = 0;
	typedef std::list<std::vector<std::pair<double, double>>>::const_iterator DataListCIt;

	for (DataListCIt it = dataList.begin(); it != dataList.end(); ++it) {
		if (it->size() > maxSize) maxSize = it->size();
	}

	std::cout << "MaxSize: " << maxSize << std::endl;
	std::cout << "ListLength: " << dataList.size() << std::endl;

	for (size_t i = 0; i < maxSize; i++) {
		for (DataListCIt it = dataList.begin(); it != dataList.end(); ++it) {
			if (it->size() > i) {
				std::cout << it->at(i).first << " " << it->at(i).second << " ";
			}
		}
		std::cout << std::endl;
	}
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

bool vec2csv(const std::vector<std::pair<double, double>>&dataList,
		const std::string &out) {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	typedef std::vector<std::pair<double, double>>::const_iterator DataVecCIt;

	for (DataVecCIt it = dataList.begin(); it != dataList.end(); ++it) {
		tmp << it->first << "," << it->second << "," << std::endl;
		file += tmp.str();
		tmp.str(std::string());
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

bool list2dat(const std::list<std::vector<std::pair<double, double>>>&dataList,
const std::string &out) {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	size_t maxSize = 0;
	typedef std::list<std::vector<std::pair<double, double>>>::const_iterator DataListCIt;

	for (DataListCIt it = dataList.begin(); it != dataList.end(); ++it) {
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
	typedef std::list<std::vector<std::pair<double, double>>>::const_iterator DataListCIt;

	for (DataListCIt it = dataList.begin(); it != dataList.end(); ++it) {
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

void flux(const std::vector<std::pair<double, double>> &data,
		std::vector<std::pair<double, double>> &diff) {
	diff.clear();
	typedef std::vector<std::pair<double, double>>::const_iterator DataVecCIt;

	for (DataVecCIt it = data.begin(); it != data.end() - 1; ++it) {
		double x = it->first;
		double y = it->second;
		double x1 = (it + 1)->first;
		double y1 = (it + 1)->second;

		diff.push_back(std::make_pair(x, (y1 - y) / (x1 - x)));
	}

}

void fluxList(const std::list<std::vector<std::pair<double, double>>>&data,
std::list<std::vector<std::pair<double, double>>> &diff) {
	diff.clear();
	std::vector<std::pair<double, double>> tmp;
	typedef std::list<std::vector<std::pair<double, double>>>::const_iterator DataListCIt;

	for (DataListCIt it = data.begin(); it != data.end(); ++it) {
		flux(*it, tmp);
		diff.push_back(tmp);
		tmp.clear();
	}
}

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

bool text2vec(const std::string &file, std::vector<std::string> &copy) {
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

bool dat2vec(const std::string &file,
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

bool dat2list(const std::string &file,
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
		dat2vec (file, stroke, x, y+1);
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

//template<class T>
bool plotList(const std::list<std::vector<std::pair<double, double>>>&dataList,const std::string &name) {
	const char* gnuplotName = "gnuplot -persis";
#ifdef _WIN32
	FILE* gnuplotpipe = _popen(gnuplotName, "w");
#else
	FILE* gnuplotpipe = popen(gnuplotName, "w");
#endif
	if (!gnuplotpipe) {
		std::cerr << ("Gnuplot not found !");
		return false;
	}
	std::stringstream tmp;
	std::string fileName = name+".dat";
	std::string path;
	path = std::string(TMPDIR) + fileName;
	list2dat(dataList, path);

	fprintf (gnuplotpipe, "set grid \n");

//			cmd("set grid");
//			cmd(std::string("set term ") + GNUPLOT_EN + std::string(" ") + atos(window));

	size_t count = 0;
	for (size_t die = 1; die <= dataList.size(); die++) {
		count++;
		if (die == 1) {
			tmp << "plot " << " '" << path << "' " << "using 1:" << (count+1) << " with linespoints pt 7 ps 0.5\n";
		}
		else {
			tmp << "replot " << " '" << path << "' " << "using 1:" << (count + 1) << " with linespoints pt 7 ps 0.5\n";
		}
	}

	fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());
	fflush (gnuplotpipe); // flush needed to start render
	fprintf(gnuplotpipe, "exit\n");
	pclose (gnuplotpipe);
	tmp.str( std::string() );
	tmp.clear();

	return true;
}

//bool normVec(const std::vector<std::pair<double, double>>&inData,
//		std::vector<std::pair<double, double>>&outData) {
//	if (!outData.empty()) {
//		outData.clear();
//	}
//	if (inData.empty())
//		return false;
//
//	typedef std::vector<std::pair<double, double>> DataVec;
//
//	for (DataVec::const_iterator jt = inData.begin(); jt != inData.end();
//			++jt) {
//		if (jt->second > 0) {
//			outData.push_back(std::make_pair(jt->first, (double) 1.0));
//		} else if (jt->second == 0) {
//			outData.push_back(std::make_pair(jt->first, (double) 0.0));
//		} else {
//			outData.push_back(std::make_pair(jt->first, (double) -1.0));
//		}
//	}
//
//	return true;
//}

bool normVec(const std::vector<std::pair<double, double>>&inData,
		std::vector<std::pair<double, double>>&outData) {
	if (!outData.empty()) {
		outData.clear();
	}
	if (inData.empty())
		return false;

	typedef std::vector<std::pair<double, double>> DataVec;

	for (DataVec::const_iterator jt = inData.begin(); jt != inData.end();
			++jt) {
		if (jt->second > 0) {
			outData.push_back(std::make_pair(jt->first, (double) 1.0));
		} else {
			outData.push_back(std::make_pair(jt->first, (double) 0.0));
		}
	}

	return true;
}

bool normList(const std::list<std::vector<std::pair<double, double>>>&inData,
std::list<std::vector<std::pair<double, double>>>&outData) {
	if (!outData.empty()) {
		outData.clear();
	}
	if(inData.empty())
	return false;
	typedef std::list<std::vector<std::pair<double, double>>> DataList;
	typedef std::vector<std::pair<double, double>> DataVec;

	DataVec tmp;

	for (DataList::const_iterator it = inData.begin(); it != inData.end(); ++it) {
		normVec (*it, tmp);
		outData.push_back(tmp);
	}
	if (!tmp.empty()) {
		tmp.clear();
	}

	return true;
}

bool normVecNoRet(std::vector<std::pair<double, double>>&inData) {
	if (inData.empty())
		return false;

	typedef std::vector<std::pair<double, double>> DataVec;
	DataVec tmp;

	for (DataVec::iterator jt = inData.begin(); jt != inData.end(); ++jt) {
		if (jt->second > 0) {
			jt->second = (float) 1.0;
		} else {
			jt->second = (float) 0.0;
		}
	}

	return true;
}

bool normListNoRet(std::list<std::vector<std::pair<double, double>>>&inData) {
	if(inData.empty())
	return false;
	typedef std::list<std::vector<std::pair<double, double>>> DataList;

	for (DataList::iterator it = inData.begin(); it != inData.end(); ++it) {
		normVecNoRet (*it);
	}

	return true;
}

bool comp(std::pair<double, double> i, std::pair<double, double> j) {
//	return (i.second < j.second);
	return (i.second > j.second);
}

double getTauVec(const std::vector<std::pair<double, double>>&dataVec) {
	if (dataVec.empty()) {
		return (double) 0.0f;
	}

	typedef std::vector<std::pair<double, double>> DataVec;
	typedef DataVec::const_iterator DataVecCIt;
	typedef std::vector<std::pair<double, double>> IntVec;
	typedef IntVec::const_iterator InVecCIt;
	InVecCIt maxIt;
	double result = 0.0f;
	IntVec intervals, ones; // withCopy
//	IntVec intervalsSort;

	for (DataVecCIt it = dataVec.begin(); it != dataVec.end(); ++it) {
		if (it->second == (double) 1.0f) {
			for (DataVecCIt jt = it + 1; jt != dataVec.end(); ++jt) {
				if (jt->second == (double) 1.0f) {
					intervals.push_back(
							std::make_pair(it->first, jt->first - it->first));
					break;
				} else {
					continue;
					//do nothing;
				}
			}
		} else {
			//do nothing
		}

		if (it->second == (double) 1.0f) {
			if (it != dataVec.end())
				ones.push_back(*it);
		}
	}

	for (auto it = ones.begin(); it != ones.end() - 1; ++it) {
		it->second = (it + 1)->first - it->first;
	}

//	intervalsSort = intervals;
//	std::sort(intervalsSort.begin(), intervalsSort.end(), comp);

	std::sort(ones.begin(), ones.end(), comp);
	if (ones[1].first < ones[0].first) {
		result = ones[1].first + ones[1].second - dataVec[0].first;
	} else if (ones[2].first < ones[0].first) {
		result = ones[2].first + ones[2].second - dataVec[0].first;
	} else {
		result = ones[3].first + ones[3].second - dataVec[0].first;
	}

#ifdef DEBUG
	std::cout << "TAU: " << result << std::endl;
#endif


//	if (!intervalsSort.empty()) {
//		intervalsSort.clear();
//	}
	if (!intervals.empty()) {
		intervals.clear();
	}
	if (!ones.empty()) {
		ones.clear();
	}

	return result;
}

//double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList) {
//
//	return (double)0.0f;
//}
