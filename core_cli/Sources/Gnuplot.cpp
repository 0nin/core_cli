/*
 * Gnuplot.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */




#include "Gnuplot.hpp"

#include "Global.hpp"

namespace Core {
Gnuplot::Gnuplot() {
	window = 0;
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
	cmd (command);
}

void Gnuplot::cmd(const std::string &command) {
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	render();
}

void Gnuplot::render(void) {
	fflush(gnuplotpipe); // flush needed to start render
}

void Gnuplot::plotDat(const std::string &dat, std::vector<size_t> &columns) {
	std::stringstream tmp;

	tmp << " ";
	for (auto it = columns.begin(); it != columns.end(); ++it) {
		tmp << *it << " ";
	}

	std::string command = "plot " + dat + " using " + tmp.str();

	cmd(command);
}

template<class T>
void Gnuplot::plot (const std::list<std::vector<std::pair<T, T>>>&dataList, const std::string &param) {
	std::stringstream tmp;
	std::string path;
	std::string fileName = "gnuplotW" + atos(window)+".dat";
	path = TMPDIR + fileName;
	list2dat(dataList, path);

	cmd("set grid");

//	plot for [col=1:4] 'file' using 0:col with lines

//	ML_FOR_ACTIVE_DIES(die) {
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

	std::string command = "plot for [col=1:" + atos(dataList.size()) << "] '" << path << "] using 0:col with linespoints pt 7 ps 0.5";
	cmd (command);

	fflush (gnuplotpipe); // flush needed to start render
	pclose (gnuplotpipe);
	tmp.str( std::string() );
	tmp.clear();

}

}
