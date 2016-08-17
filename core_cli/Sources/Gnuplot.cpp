/*
 * Gnuplot.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#include "Gnuplot.hpp"
#include "Global.hpp"

#include <cstdio>
#include <sstream>
#include <fstream>



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

void Gnuplot::plotDat(const std::string &dat, size_t col) {
	std::stringstream tmp;

	cmd("set grid");
	for (size_t die = 1; die <= col; die++) {
		if (die == 1) {
			tmp << "plot " << " '" << dat << "' " << "using 1:" << (die + 1)
					<< " with linespoints pt 7 ps 0.5" << std::endl;
		} else {
			tmp << "replot " << " '" << dat << "' " << "using 1:" << (die + 1)
					<< " with linespoints pt 7 ps 0.5" << std::endl;
		}

		fprintf(gnuplotpipe, "%s \n", tmp.str().c_str());
		tmp.str(std::string());
		tmp.clear();
	}

	window++;
}

void Gnuplot::plot(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &param) {
	std::stringstream tmp;
	std::string path;
	std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
	while (!fileExist(fileName)) {
		fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
	}
#ifndef _WIN32
	path = std::string("/tmp/") + fileName;
#else
	path = std::string("./tmp/") + fileName;
#endif
	list2dat(dataList, path);
	cmd("set grid");
	cmd(std::string("set term ") + GNUPLOT_EN + std::string(" ") + atos(window));

	for (size_t die = 1; die <= 2*dataList.size(); die+=2) {
		if (die == 1) {
			tmp << "plot " << " '" << path << "' " << "using " << die << ":" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
		}
		else {
			tmp << "replot " << " '" << path << "' " << "using " << die << ":" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
		}
	}

	std::string command = tmp.str();
	cmd (command);

	tmp.str( std::string() );
	tmp.clear();
	window++;
}

void Gnuplot::run(const std::string &script) {
	//TODO:
}

}
