/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#include "Common.h"
#include "Global.h"

#include <cstdio>
#include <sstream>
#include <fstream>

#ifdef WIN32
//    #define GNUPLOT_NAME "pgnuplot -persist"
#define GNUPLOT_NAME "gnuplot -persis"
#else
#define GNUPLOT_NAME "gnuplot -persis"
#endif

namespace Core {

class Gnuplot {
public:
	Gnuplot();
	Gnuplot(const std::string &plot);
	virtual ~Gnuplot();
	template<class T>
	void addCurve(const std::string &name,
			const std::list<std::vector<std::pair<T, T>>>&dataLis, const std::string &attributes);
	void cmd (const std::string &command);
	void plot (const std::string &dat, std::vector<size_t> &col);
	void run (const std::string &script);
	void operator<<(const std::string & command);
	void render(void);
//	template<class T> void operator<<(std::pair<T, T> point);

protected:
	FILE *gnuplotpipe;
	std::vector<std::string> curves;
};

Gnuplot::Gnuplot() {
#ifdef WIN32
	gnuplotpipe = _popen(GNUPLOT_NAME, "w");
#else
	gnuplotpipe = popen(GNUPLOT_NAME, "w");
#endif

	if (!gnuplotpipe) {
		std::cerr << ("Gnuplot not found !");
	}
}
Gnuplot::~Gnuplot() {
	fprintf(gnuplotpipe, "exit\n");

#ifdef WIN32
	_pclose(gnuplotpipe);
#else
	pclose(gnuplotpipe);
#endif
}

void Gnuplot::operator<<(const std::string &command) {
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	render();
}

void Gnuplot::cmd(const std::string &command) {
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	render();
}

void Gnuplot::render(void) {
	fflush(gnuplotpipe); // flush needed to start render
}

template<class T>
void Gnuplot::addCurve(const std::string &name,
		const std::list<std::vector<std::pair<T, T>>>&dataLis, const std::string &attributes) {
	curves.push_back(name);

	std::string out = name+".dat";
	vec2dat (dataLis, out, "");
//	plot ()

}

void Gnuplot::plot(const std::string &dat, std::vector<size_t> &col) {
	std::stringstream tmp;

	tmp << " ";
	for (auto it = col.begin(); it != col.end(); ++it) {
		tmp << *it << " ";
	}

	std::string command = "plot " + dat + " using " + tmp.str();

	cmd(command);
}

//template<class T> void Gnuplot::operator<<(std::pair<T, T> point) {
//	fprintf(gnuplotpipe, "%s\n", cmd.c_str());
//	fflush(gnuplotpipe); // flush needed to start render+
//}
}
#endif /* GNUPLOT_HPP_ */
