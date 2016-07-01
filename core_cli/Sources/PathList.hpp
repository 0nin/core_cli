#ifndef _PathList_h_
#define _PathList_h_

#include "Common.hpp"

namespace Core
{

class PathList
{
public:
	PathList(void);

	virtual ~PathList(void);

public:
	virtual void addPath(const std::string &path);

	virtual void clearPaths(void);

//	virtual bool getFilePath(const std::string &fileName, std::string &fullPath);

	virtual bool getPath(const std::string &fileName, std::string &fullPath);

	static PathList* getSingletonPtr(void);

//	static PathList getSingleton(void);

	virtual void print(void);

protected:
//	std::string path;
	std::vector<std::string> pathList;
};
// class PathList

} /* namespace Core */
#endif // _PathList_h_
