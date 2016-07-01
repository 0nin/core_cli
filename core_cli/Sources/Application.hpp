#ifndef _Application_h_
#define _Application_h_

#include "Common.hpp"
#include "Engine.hpp"
#include "Console.hpp"

namespace Core
{
/**
 * 
 */
class Application: public CppReadline::Console
{
protected:
	bool _exit;
	std::string config;
	std::string path;
public:
	/**
	 *
	 */
//    explicit Application (void);
	explicit Application(std::string path, std::string configFile);

	virtual ~Application(void);

	void init(void);

	void loop(void);

    void go (void);
//
	void handle(std::string msg);
//
	void kill(void);

	void clear(void);

	virtual void quit(void);
};
// class Application

}
#endif // #ifndef _Application_h_
