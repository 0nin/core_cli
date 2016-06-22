#ifndef _Script_h_
#define _Script_h_

#include "Common.hpp"
#include "Table.hpp"
#include "TextFile.hpp"

namespace Core {
/**
 *
 */
class Library: public Table, public TextFile {
protected:

	unsigned currentString;

	std::string currentFileName;

	std::string currentClaster;

	std::string currentSpace;

	std::string currentType;

public:
	explicit Library();

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
