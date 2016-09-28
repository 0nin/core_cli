/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_


#include "Conv.hpp"
#include "Global.hpp"
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#ifdef _WIN32
#define TMPDIR "./tmp/"
#else
#define TMPDIR "/tmp/"
#endif


#define GNUPLOT_EN "wxt"
#define GNUPLOT_NAME "gnuplot"

namespace Core {



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

	void send(const std::string &command) {
		fprintf(gnuplotpipe, "%s\n", command.c_str());
		render();
	}

//	struct compare {
//		template <class Val1, class Val2>
//		bool operator() (const std::vector<std::pair<Val1, Val2>> &i, const std::vector<std::pair<Val1, Val2>> &j) {
//			return (i.size() > j.size());
//		}
//	} c;

	template <class Val1, class Val2>
	void send(const std::list<std::vector<std::pair<Val1, Val2>>>&arg) {
		std::string tmp;

		size_t maxSize=0;
		for (auto it = arg.begin(); it != arg.end(); ++it) {
			if (it->size() > maxSize) maxSize = it->size();
		}

		for (size_t i = 0; i < maxSize; i++) {
			for (auto it = arg.begin(); it != arg.end(); ++it) {
				if (it->size() > i) {
					tmp += std::to_string(it->at(i).first) + " " + std::to_string(it->at(i).second) + " ";
				}
			}

			this->send(tmp);
			tmp.clear();
		}

		this->send("e\n");
	}

	template <class Val1, class Val2>
	void send(const std::vector<std::pair<Val1, Val2>> &arg) {
		for (auto it = arg.begin(); it != arg.end(); ++it) {
			this->send(std::to_string(it->first) + " " + std::to_string(it->second));
		}
		this->send("e\n");
	}


//	void operator<<(const std::string &command) {
//		cmd(command);
//	}
//
//	template <class Val1, class Val2>
//	void operator<<(const std::list<std::vector<std::pair<Val1, Val2>>> &arg) {
//		send(arg);
//	}
//
//	template <class Val1, class Val2>
//	void operator<<(const std::vector<std::pair<Val1, Val2>> &arg) {
//		send(arg);
//	}



	template<class Val1, class Val2>
	void plot(const std::list<std::vector<std::pair<Val1, Val2>>>&dataList,const std::string &param="") {
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

	template<class Val1, class Val2>
	void plot(const std::vector<std::pair<Val1, Val2>>&dataVec,const std::string &param="") {
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
//		cmd("exit");
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
