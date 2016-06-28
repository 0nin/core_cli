#ifndef _File_h_
#define _File_h_

#include "Common.hpp"

namespace Core
{

//class Library;

//template<class T>
//extern std::string atos(T _t);

class TextFile
{
public:
	TextFile(const std::string &fileName);

	virtual ~TextFile(void);

	friend class Library;

public:
	void print(void);

	virtual void write(std::string & text);

	virtual void clear(void);

	static void write(std::string & text, std::string & name);

	static void clear(std::string & name);

	void copyByStrokes(void);

	void copyByStrokes(std::string & name);

//	void copyByWords(void);

//	void copyByWords(std::string fileName);

	virtual void setName(std::string &name);

protected:
	std::string fileName;
	std::string fullPath;
	std::string mode;
	std::vector<std::string> fileCopy;

};
// class File;
} /* namespace Core */

#endif // #ifndef _TextFile_h_

