#ifndef _Path_h_
#define _Path_h_

#include "Common.h"

//#include <string>
//#include <vector>

namespace Core {

class PathList
//:public Uncopy
{
public:
  explicit PathList();
  virtual ~PathList ();
  virtual void addPath( const std::string &path);
  virtual void clearPaths();
  virtual std::string getFilePath( const std::string &file/*, std::string &path*/);
  virtual std::string getPath( const std::string &file/*, std::string &path*/);
  static PathList* getSingletonPtr();
  static PathList getSingleton();
  virtual void print();

private:
  std::vector<std::string> _pathList;
}; // class PathList;

}
#endif // _Path_h_
