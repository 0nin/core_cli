#ifndef _Application_h_
#define _Application_h_

#include "Common.h"
#include "Console.hpp"

#if defined __WIN32__ || _WIN32 && defined _MSC_VER
#define PLATFORM WIN32_VISUAL
#else
#define PLATFORM UNIX
#endif


namespace Core {

class Application {
public:
	explicit Application(const std::string &path, const std::string &configFile);
	virtual ~Application(void);
	void init(void);
	void loop(void);
	void go(void);
	void handle(const std::string &msg);
	void kill(void);
	void clear(void);
	virtual void quit(void);

protected:
	CppReadline::Console cs;
	bool _exit;
	std::string config;
	std::string path;
};
// class Application

}
#endif // #ifndef _Application_h_
