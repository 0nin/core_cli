/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#ifdef CORELIB

#include "Common.h"
#include "Conv.hpp"
#include "Global.h"

#else
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#define TMPDIR "./tmp/"
#else
#define TMPDIR "/tmp/"
#endif
define DUMMY 999.99f
#endif

#define GNUPLOT_EN "wxt"
#define GNUPLOT_NAME "gnuplot"

namespace Core {

//class Plot {
//public:
//
//	explicit Plot() {
//
//	}
//	virtual ~Plot() {
//
//	}
//
//	std::string path;
//	std::list<std::vector<std::pair<double, double>>>*data;
//	std::vector<std::string> title;
//	std::vector<std::string> window;
//	std::string style;
//	//protected:
//};

class Gnuplot {
public:

	explicit Gnuplot() {
#ifdef _WIN32
		gnuplotpipe = _popen(GNUPLOT_NAME, "w");
#else
		gnuplotpipe = popen(GNUPLOT_NAME, "w");
#endif

		if (!gnuplotpipe) {
				std::cerr << ("Gnuplot not found !");
			}
	}

	virtual ~Gnuplot() {
		cleanup();
		close();
	}

	void cmd(const std::string &command) {
		fprintf(gnuplotpipe, "%s\n", command.c_str());
		render();
	}

	void operator<<(const std::string &command) {
		cmd(command);
	}


	template<class Float1, class Float2>
	void plot(const std::list<std::vector<std::pair<Float1, Float2>>>&dataList,const std::string &param="") {
				std::stringstream tmp;
				std::string path;
				std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
				std::vector<std::string> plotDatFiles;

				for (auto it = dataList.begin(); it != dataList.end(); ++it) {
					fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
#ifndef _WIN32
					path = std::string("/tmp/") + fileName;
#else
					path = std::string("./tmp/") + fileName;
#endif
					plotDatFiles.push_back(path);
					this->tmpFiles.push_back(path);
					Conv::vec2dat (*it, path);
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

		std::string command = tmp.str();
		cmd (command);

		tmp.str( std::string() );
		tmp.clear();
		this->window++;
	}

	template<class Float1, class Float2>
	void plot(const std::vector<std::pair<Float1, Float2>>&dataVec,const std::string &param="") {
		std::stringstream tmp;
		std::string path;
		std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
		std::vector<std::string> plotDatFiles;

//		for (auto it = dataList.begin(); it != dataList.end(); ++it) {
			fileName = "gnuplot" + atos(window) + "_" + rand(3) + ".dat";
#ifndef _WIN32
			path = std::string("/tmp/") + fileName;
#else
			path = std::string("./tmp/") + fileName;
#endif
			plotDatFiles.push_back(path);
			this->tmpFiles.push_back(path);
			Conv::vec2dat(dataVec, path);
//			Conv::vec2dat(*it, path);
//		}

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

		std::string command = tmp.str();
		cmd (command);

		tmp.str( std::string() );
		tmp.clear();
		this->window++;
	}


	void plotDat(const std::string &path, size_t col) {
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


	void run(const std::string &script) {
		//TODO:
	}

	void render(void) {
		fflush(gnuplotpipe); // flush needed to start render
	}

	void cleanup(void) {
		if(!tmpFiles.empty()) {
			for (auto it = tmpFiles.begin(); it != tmpFiles.end(); ++it) {
				if (fileExist(*it)) remove(it->c_str());
			}
		}
	}

	void close(void) {
	cmd("exit");
	#ifdef _WIN32
		_pclose(gnuplotpipe);
	#else
		cmd("exit");
		pclose(gnuplotpipe);
	#endif
	}

protected:
	FILE *gnuplotpipe = nullptr;
	size_t window = 0;
//	std::vector<Plot> plots;
	std::vector<std::string> tmpFiles;
};

}
#endif /* GNUPLOT_HPP_ */
