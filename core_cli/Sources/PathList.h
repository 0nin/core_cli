#ifndef _PathList_h_
#define _PathList_h_

#include "Common.hpp"

//#include "Uncopy.h"

//#include <string>
//#include <vector>

namespace Core {

class PathList : public Uncopy
{
public:
  explicit PathList();

  virtual ~PathList ();

  virtual void addPath(const std::string &path);

  virtual void clearPaths();

  virtual std::string getFilePath(const std::string &fileName);

  virtual std::string getPath(const std::string &fileName);

  static PathList* getSingletonPtr();

  static PathList getSingleton();

  virtual void print();

protected:
  std::vector <std::string> pathList;
}; // class PathList

} /* namespace Core */
#endif // _PathList_h_
