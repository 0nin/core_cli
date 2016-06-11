#ifndef _File_h_
#define _File_h_

#include <string>
#include <list>
#include <vector>

namespace Core {

class Library;

class TextFile {
protected:
	std::string fileName;
	std::vector<std::string> fileCopy;
	friend class Library;

public:
	TextFile();
	TextFile(std::string fileName);
	virtual ~TextFile();

public:
	void print();
	virtual void write(std::string text);
	virtual void clear();
	static void write(std::string text, std::string fileName);
	static void clear(std::string fileName);
	template<class T> static std::string atos( /*double*/T real);
	void copyByStrokes();
	void copyByStrokes(std::string fileName);
	void copyByWords();
	void copyByWords(std::string fileName);
	virtual void bindFile(std::string fileName);
};
// class File;
}

#endif // #ifndef _File_h_

