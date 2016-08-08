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
#define GNUPLOT_EN "qt"
#endif

#define TMPGNUT "tmpxtd.gnu"

namespace Core {

class Gnuplot {
public:
	Gnuplot();
//	Gnuplot(const std::string &plot);
	virtual ~Gnuplot();
//	template<class T>
//	void addPoint(std::pair<T, T> point);
//	template<class T>
//	void addCurve(const std::string &name,
//			const std::list<std::vector<std::pair<T, T>>>&dataLis, const std::string &attributes);
//	void a
	void cmd (const std::string &command);
//	void plot (const std::string &dat, std::vector<size_t> &col);
//	template<class T>
	void plot (const std::list<std::vector<std::pair<double, double>>>&dataLis, const std::string &param);
	void plotDat (const std::string &dat, std::vector<size_t> &columns);
	void run (const std::string &script);
//	void run (const std::string &script);
	void operator<<(const std::string & command);
	void render(void);
	void close(void);
//	template<class T> void operator<<(std::pair<T, T> point);

protected:
	FILE *gnuplotpipe;
	size_t window;
};

}
#endif /* GNUPLOT_HPP_ */
