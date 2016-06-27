#ifndef _PathList_h_
#define _PathList_h_

#include "Common.hpp"

namespace Core
{

class PathList
{
public:
	explicit PathList();

	virtual ~PathList();

public:
	virtual void addPath(const std::string &path);

	virtual void clearPaths();

//	virtual bool getFilePath(const std::string &fileName, std::string &fullPath);

	virtual bool getPath(const std::string &fileName, std::string &fullPath);

	static PathList* getSingletonPtr();

	static PathList getSingleton();

	virtual void print();

protected:
//	std::string path;
	std::vector<std::string> pathList;
};
// class PathList

} /* namespace Core */
#endif // _PathList_h_
