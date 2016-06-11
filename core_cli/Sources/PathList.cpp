// #include "Exception.h"
#include "PathList.h"

#if defined __WIN32__ || _WIN32 && _MSC_VER
#pragma warning (disable : 4996)
#else
//
#endif

//using namespace std;
//using namespace Core;

namespace Core {

static PathList instance;
std::string path;

PathList::PathList() {
	const char *env = getenv("PATH");

	//search local paths first, in-case someone has the SDK installed while hacking another copy
	_pathList.push_back("./");  // present directory
	_pathList.push_back("../"); // back one
	_pathList.push_back("../../"); // back two
	if (env) {
		_pathList.push_back(std::string(env) + "/"); // Path lacks a terminating slash
	}
}

PathList::~PathList() {
	clearPaths ();
}


void PathList::addPath(const std::string &path) {
	_pathList.push_back(path);
}

void PathList::clearPaths() {
	_pathList.clear();
}

std::string PathList::getFilePath(
		const std::string &file/*, std::string &path*/) {
	std::string pathString;

	for (auto it = _pathList.begin(); it != _pathList.end(); it++) {
		pathString = *it + file;
		FILE *fp = fopen(pathString.c_str(), "rb");
		if (fp) {
			fclose(fp);
			path = pathString;
			//return true;
			return path;
		}
	}
	throw Exception("File with name " + file + " doesn't exist;");
	//return false;
}

std::string PathList::getPath(const std::string &file/*, std::string &path*/) {
	std::string pathString;

	for (auto it = _pathList.begin(); it != _pathList.end(); it++) {
		pathString = *it + file;
		FILE *fp = fopen(pathString.c_str(), "rb");
		if (fp) {
			fclose(fp);
			path = *it;
			//return true;
			return path;
		}
	}
	//return false;
	throw Exception("File with name" + file + "doesn't exist");
}

PathList* PathList::getSingletonPtr() {
	return &instance;
}

PathList PathList::getSingleton() {
	return instance;
}

void PathList::print() {
	for (auto it = _pathList.begin(); it != _pathList.end();
			it++) {
		std::cout << *(it) << std::endl;
	}
}

} /* namespace Core */
