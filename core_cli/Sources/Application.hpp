#ifndef _Application_h_
#define _Application_h_

#include "Common.hpp"
#include "Engine.hpp"
#include "Console.hpp"
#include "Uncopy.hpp"

namespace Core
{
/**
 * 
 */
class Application: public Engine, public CppReadline::Console, public Uncopy
{
protected:
	bool _exit;
	std::string config;
	std::string path;
public:
	/**
	 *
	 */
//    explicit Application ();
	explicit Application(std::string path, std::string configFile);

	virtual ~Application();

	void init();

	void loop();

//    void go ();
//
	void handle(std::string msg);
//
	void kill();

	virtual void quit();
};
// class Application

}
#endif // #ifndef _Application_h_
