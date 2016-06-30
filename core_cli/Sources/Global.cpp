#include "gnuplot-iostream.h"

#include "Global.hpp"

#include "Application.hpp"
#include "Console.hpp"
#include "Exception.hpp"



namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

unsigned info(const std::vector<std::string> &)
{
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

// In this command we implement a basic calculator
unsigned calc(const std::vector<std::string> & input)
{
	if (input.size() != 4)
	{
		// The first element of the input array is always the name of the
		// command as registered in the console.
		std::cout << "Usage: " << input[0] << " num1 operator num2\n";
		// We can return an arbitrary error code, which we can catch later
		// as Console will return it.
		return 1;
	}
	double num1 = std::stod(input[1]), num2 = std::stod(input[3]);

	char op = input[2][0];

	double result;
	switch (op)
	{
	case '*':
		result = num1 * num2;
		break;
	case '+':
		result = num1 + num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	default:
		std::cout << "The inserted operator is not supported\n";
		// Again, we can return an arbitrary error code to catch it later.
		return 2;
	}
	std::cout << "Result: " << result << '\n';
	return 0;
}

int main(int argc, char *args[])
{
	try
	{
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e)
	{
		Core::Exception::die(e.getDescription(), std::string("error.log"));
		return 1;
	}
	return 0;
}

//int main()
//{
//	Gnuplot gp;
//
//	std::vector<std::pair<double, double> > xy_pts_A;
//	for(double x=-2; x<2; x+=0.01) {
//		double y = x*x*x;
//		xy_pts_A.push_back(std::make_pair(x, y));
//	}
//
//	std::vector<std::pair<double, double> > xy_pts_B;
//	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
//		double theta = alpha*2.0*3.14159;
//		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
//	}
//
//	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
//	// Data will be sent via a temporary file.  These are erased when you call
//	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
//	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
//	// and won't be deleted (this is useful when creating a script).
//	gp << "plot" << gp.file1d(xy_pts_A) << "with lines title 'cubic',"
//		<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;
//
//
//	return 0;
//}
