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
	render();
//	fflush(gnuplotpipe); // flush needed to start render
//	fprintf(gnuplotpipe, "exit\n");
#ifdef _WIN32
	_pclose(gnuplotpipe);
#else
	pclose(gnuplotpipe);
#endif
}

void Gnuplot::plotDat(const std::string &dat, std::vector<size_t> &columns) {
	std::stringstream tmp;

//	tmp << " ";
	size_t die = 1;
	cmd("set grid");
//	cmd(std::string("set term ") + GNUPLOT_EN + std::string(" ") + atos(window));
//	window++;
	for (auto it = columns.begin(); it != columns.end(); ++it) {
//		tmp << *it << " ";
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
		die++;
	}

//	for (size_t die = 1; die !=dataList.size(); ++die) {
//		if (die == 1) {
//			tmp << "plot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
//		}
//		else {
//			tmp << "replot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5" <<std::endl;
//		}
//
//		fprintf (gnuplotpipe, "%s \n", tmp.str ().c_str ());
//	}

//	std::string command = "plot '" + dat + "' using" + tmp.str();
//
//	cmd(command);
	window++;
}

//template<class T>
void Gnuplot::plot(const std::list<std::vector<std::pair<double, double>>>&dataList, const std::string &param) {
	  std::stringstream tmp;
	  std::string path;
	  std::string fileName = "gnuplot" + atos(window)+".dat";
	#ifndef _WIN32
	  path = std::string("/tmp/") + fileName;
	#else
	  path = std::string("./tmp/") + fileName;
	#endif
	  list2dat(dataList, path);
	  cmd("set grid");
	  cmd(std::string("set term ") + GNUPLOT_EN + std::string(" ") + atos(window));
	//  cmd("set term qt " + atos(window));

	//  plot for [col=1:4] 'file' using 0:col with lines

	//  ML_FOR_ACTIVE_DIES(die) {
	//  for (size_t die = 1; die <= dataList.size(); die++) {
	//    if (die == 1) {
	//      tmp << "plot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
	//    }
	//    else {
	//      tmp << "replot " << " '" << path << "' " << "using 1:" << (die + 1) << " with linespoints pt 7 ps 0.5" << std::endl;
	//    }

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

	//  cmd ("plot")

	  tmp.str( std::string() );
	  tmp.clear();
	  window++;
}

void Gnuplot::run(const std::string &script) {
	//TODO:
}

}
