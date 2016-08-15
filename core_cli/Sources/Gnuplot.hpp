/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#include "Common.h"

#ifdef _WIN32
//    #define GNUPLOT_NAME "pgnuplot -persist"
#define GNUPLOT_NAME "gnuplot -persis"
#else
#define GNUPLOT_NAME "gnuplot -persis"
#endif

#ifdef _WIN32
//    #define GNUPLOT_NAME "pgnuplot -persist"
#define GNUPLOT_EN "wxt"
#else
//#define GNUPLOT_EN "qt"
#define GNUPLOT_EN "wxt"
#endif

#define TMPGNUT "tmpxtd.gnu"

namespace Core {

class Gnuplot {
public:
	Gnuplot();
	virtual ~Gnuplot();
	void cmd (const std::string &command);
	void plot (const std::list<std::vector<std::pair<double, double>>>&dataLis, const std::string &param="");
	void plotDat (const std::string &dat, size_t col);
	void run (const std::string &script);
	void operator<<(const std::string & command);
	void render(void);
	void close(void);

protected:
	FILE *gnuplotpipe;
	size_t window;
};

}
#endif /* GNUPLOT_HPP_ */
