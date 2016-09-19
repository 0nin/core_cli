#ifndef _Script_h_
#define _Script_h_

#include "Common.h"
#include "Table.hpp"
#include "TextFile.hpp"

namespace Core {
/**
 *
 */
class Library: public Table {
public:
	Library(void);

	virtual ~Library(void);

public:
	virtual void loadConfigFile(std::string fileName);

	virtual void configStroke(std::string stroke);

	virtual void clear(void);

	virtual void addParam(std::string x, std::string y);

	std::string getParam(std::string param);

//	static Library getSingleton(void);

	static Library* getSingletonPtr(void);

	virtual void printAllPaths(void);

	virtual void printAll(void);

protected:
	size_t currentString=0;

	std::string currentFileName;

	std::string currentClaster;

	std::string currentSpace;

	std::string currentType;

	TextFile scriptCopy=std::string("");
};
// class Decoder

}
#endif // #ifndef _Manager_h_
