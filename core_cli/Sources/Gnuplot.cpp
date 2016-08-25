/*
 * Gnuplot.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#include "Gnuplot.hpp"
#include <cstdio>
#include <sstream>
#include <fstream>
#include "Global.h"
#include "Conv.h"

#define GNUPLOT_EN "wxt"
#define GNUPLOT_NAME "gnuplot"

using namespace Conv;

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

namespace Core {
Gnuplot::Gnuplot() {
	window = 0;
#ifdef _WIN32
	gnuplotpipe = _popen(GNUPLOT_NAME, "w");
#else
	gnuplotpipe = popen(GNUPLOT_NAME, "w");
#endif

	if (!gnuplotpipe) {
		std::cerr << ("Gnuplot not found !");
	}
}
Gnuplot::~Gnuplot() {
	close();
}

void Gnuplot::operator<<(const std::string &command) {
	cmd(command);
}

void Gnuplot::cmd(const std::string &command) {
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	render();
}

void Gnuplot::render(void) {
	fflush(gnuplotpipe); // flush needed to start render
}

void Gnuplot::close(void) {
//	render();
//	fprintf(gnuplotpipe, "exit\n")
//	render();
	cmd("exit");
#ifdef _WIN32
	_pclose(gnuplotpipe);
#else
	cmd("exit");
	pclose(gnuplotpipe);
#endif
}

void Gnuplot::plotDat(const std::string &path, size_t col) {
	std::stringstream tmp;

	cmd("set grid");
	cmd(
			std::string("set term ") + GNUPLOT_EN + std::string(" ")
					+ atos(window));

	for (size_t die = 1; die <= 2 * col; die += 2) {
		if (die == 1) {
			tmp << "plot " << " '" << path << "' " << "using " << die << ":"
					<< (die + 1) << " with linespoints pt 7 ps 0.5"
					<< std::endl;
		} else {
			tmp << "replot " << " '" << path << "' " << "using " << die << ":"
					<< (die + 1) << " with linespoints pt 7 ps 0.5"
					<< std::endl;
		}
	}

	std::string command = tmp.str();
	cmd(command);

	tmp.str(std::string());
	tmp.clear();

	window++;
}

void Gnuplot::plot(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &param) {
	std::stringstream tmp;
	std::string path;
	std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
	std::vector<std::string> plotDatFiles;

	typedef std::list<std::vector<std::pair<double, double>>> DataList;
	typedef DataList::const_iterator DataListCIt;
	for (DataListCIt it = dataList.begin(); it != dataList.end(); ++it) {
//		while (!fileExist(path)) {
			fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
#ifndef _WIN32
			path = std::string("/tmp/") + fileName;
#else
			path = std::string("./tmp/") + fileName;
#endif
			plotDatFiles.push_back(path);
//		}
		vec2dat (*it, path);
	}

	cmd("set grid");
	cmd(std::string("set term ") + GNUPLOT_EN + std::string(" ") + atos(window));

	//	list2dat(dataList, path);
	typedef std::vector<std::string> StringVec;
	typedef StringVec::const_iterator StringVecCIt;

	for (StringVecCIt it = plotDatFiles.begin(); it != plotDatFiles.end(); ++it) {
		if (it == plotDatFiles.begin()) {
			tmp << "plot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
		}
		else {
			tmp << "replot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
		}

	}

//	for (size_t die = 1; die <= 2*dataList.size(); die+=2) {
//		if (die == 1) {
//			tmp << "plot " << " '" << plotDatFiles[fileN] << "' " << "using " << die << ":" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
//		}
//		else {
//			tmp << "replot " << " '" << plotDatFiles[fileN] << "' " << "using " << die << ":" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
//		}
//		fileN++;
//	}

	std::string command = tmp.str();
	cmd (command);

	tmp.str( std::string() );
	tmp.clear();
	this->window++;
}

void Gnuplot::run(const std::string &script) {
	//TODO:
}

}
