#ifndef _Script_h_
#define _Script_h_

//#include <map>
//#include <list>
//#include <vector>

//#include "Uncopy.h"
#include "Common.h"
#include "Table.h"

#include "TextFile.h"

namespace Core {
/**
 *
 */
class Library : public Table
{
protected:
	TextFile scriptCopy;
	std::map <std::string, std::string> table;
	unsigned currentString;
	std::string currentFileName;
	std::string currentClaster;
	std::string currentSpace;
	std::string currentType;

public:
	Library();
	virtual ~Library();
	virtual void loadConfigFile(std::string fileName);
	virtual void configStroke(std::string stroke);
	virtual void clear();
	virtual void addParam(std::string x, std::string y);
	std::string getParam(std::string param);
	static Library getSingleton();
	static Library* getSingletonPtr();
	virtual void printAllPaths();
	virtual void printAll();
};
// class Decoder

}
#endif // #ifndef _Manager_h_
