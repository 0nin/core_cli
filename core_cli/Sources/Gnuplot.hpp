/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#include "Common.h"

namespace Core {

class Plot {
public:
	explicit Plot() {

	}
	virtual ~Plot() {

	}

	std::string path;
	std::list<std::vector<std::pair<double, double>>>*data;
	std::vector<std::string> title;
	std::vector<std::string> window;
	std::string style;
	//protected:
};

class Gnuplot {
public:
	explicit Gnuplot();
	virtual ~Gnuplot();
	void cmd(const std::string &command);
	void plot(const std::list<std::vector<std::pair<double, double>>>&dataLis,const std::string &param="");
	void plotDat (const std::string &dat, size_t col);
	void run (const std::string &script);
	void operator<<(const std::string & command);
	void render(void);
	void close(void);

protected:
	FILE *gnuplotpipe;
	size_t window;
	std::vector<Plot> plots;
	std::vector<std::string> tmpFiles;
};

}
#endif /* GNUPLOT_HPP_ */
