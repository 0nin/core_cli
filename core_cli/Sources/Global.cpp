#include "Application.h"
#include "Exception.h"
#include "Global.h"

extern int _main(int argc, char* args[]) {
	try {
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e) {
		Core::Exception::die(e.getDescription(), std::string("error.log"));
		return 1;
	}
	return 0;
}
