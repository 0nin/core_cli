/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#include <cstdio>
#include <string>
#include <iostream>

#ifdef WIN32
//    #define GNUPLOT_NAME "pgnuplot -persist"
#define GNUPLOT_NAME "gnuplot"
#else
#define GNUPLOT_NAME "gnuplot"
#endif

//using std::string;
//using std::cerr;

class Gnuplot
{
public:
	Gnuplot();
	Gnuplot (const std::string &plot);
	~Gnuplot();
//	void operator() (const std::string & command);
	void operator<< (const std::string & a);
	void render (void);
	template<class T> void operator<< (std::pair<T, T> point);

protected:
	FILE *gnuplotpipe;
};

Gnuplot::Gnuplot()
{
#ifdef WIN32
	gnuplotpipe = _popen(GNUPLOT_NAME, "w");
#else
	gnuplotpipe = popen(GNUPLOT_NAME, "w");
#endif

	if (!gnuplotpipe)
	{
		std::cerr << ("Gnuplot not found !");
	}
}
Gnuplot::~Gnuplot()
{
	fprintf(gnuplotpipe, "exit\n");

#ifdef WIN32
	_pclose(gnuplotpipe);
#else
	pclose(gnuplotpipe);
#endif
}
//void Gnuplot::operator()(const std::string & command)
//{
//	fprintf(gnuplotpipe, "%s\n", command.c_str());
//	fflush(gnuplotpipe); // flush needed to start render
//}

void Gnuplot::operator<<(const std::string & command)
{
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	fflush(gnuplotpipe); // flush needed to start render
}

void Gnuplot::render(void)
{
	fflush(gnuplotpipe); // flush needed to start render
}

template<class T> void Gnuplot::operator<<(std::pair<T, T> point)
{
//	fprintf(gnuplotpipe, "%s\n", command.c_str());
//	fflush(gnuplotpipe); // flush needed to start render+

}



#endif /* GNUPLOT_HPP_ */
