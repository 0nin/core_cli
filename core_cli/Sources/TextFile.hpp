#ifndef _File_h_
#define _File_h_

#include "Common.hpp"

namespace Core
{

//class Library;

template<class T>
extern std::string atos(T _t);

class TextFile
{
protected:
	std::string fileName;
	std::vector<std::string> fileCopy;
//	friend class Library;

public:
	explicit TextFile();

	explicit TextFile(std::string fileName);

	virtual ~TextFile();

public:
	void print();

	virtual void write(std::string text);

	virtual void clear();

	static void write(std::string text, std::string fileName);

	static void clear(std::string fileName);

	void copyByStrokes();

	void copyByStrokes(std::string fileName);

	void copyByWords();

	void copyByWords(std::string fileName);

	virtual void attachFile(std::string fileName);
};
// class File;
} /* namespace Core */

#endif // #ifndef _TextFile_h_

