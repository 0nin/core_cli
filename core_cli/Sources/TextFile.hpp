#ifndef _File_h_
#define _File_h_

#include "Common.hpp"

namespace Core
{

//class Library;

//template<class T>
//extern const std::string atos(T _t);

class TextFile
{
public:
	friend class Library;

	explicit TextFile(const std::string &fileName);

	virtual ~TextFile(void);

	void operator<<(const std::string &str);

	void print(void);

	virtual void write(const std::string &text);

	virtual void clear(void);

	static void write(const std::string &text, const std::string &name);

	static void clear(const std::string &name);

	virtual void copy(void);

//	virtual void copyByStrokes(const std::string & name);

//	void copyByWords(void);

//	void copyByWords(const std::string fileName);

	virtual void setFile(const std::string &name);

private:
	TextFile(const TextFile&) = delete;
	TextFile(TextFile&&) = delete;
	TextFile& operator =(TextFile const&) = delete;
	TextFile& operator =(TextFile&&) = delete;


	std::string fileName;
//	std::string fullPath;
	std::string mode;
	std::vector<std::string> fileCopy;

};
// class File;
} /* namespace Core */

#endif // #ifndef _TextFile_h_

