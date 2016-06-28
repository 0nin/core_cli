#ifndef _Script_h_
#define _Script_h_

#include "Common.hpp"
#include "Table.hpp"
#include "TextFile.hpp"

namespace Core
{
/**
 *
 */
class Library: public Table
{
protected:

	unsigned currentString;

	std::string currentFileName;

	std::string currentClaster;

	std::string currentSpace;

	std::string currentType;

	Core::TextFile scriptCopy;

public:
	Library(void);

	virtual ~Library(void);

	virtual void loadConfigFile(std::string fileName);

	virtual void configStroke(std::string stroke);

	virtual void clear(void);

	virtual void addParam(std::string x, std::string y);

	std::string getParam(std::string param);

//	static Library getSingleton(void);

	static Library* getSingletonPtr(void);

	virtual void printAllPaths(void);

	virtual void printAll(void);
};
// class Decoder

}
#endif // #ifndef _Manager_h_
