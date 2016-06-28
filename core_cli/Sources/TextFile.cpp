//#if defined _WIN32 || __WIN32__
//#pragma warning (disable : 4996)
//#else
//
//#endif

#include "TextFile.hpp"
#include "PathList.hpp"
#include "Exception.hpp"

#include <sstream>
#include <fstream>

namespace Core
{

void TextFile::write(std::string text, std::string fileName)
{
	std::ofstream mFile;
	mFile.open(fileName.c_str());
	if (mFile.is_open())
	{
		mFile << text;
		mFile.close();
		//return true;
	}
	else
		throw Exception(std::string("I can't write to") + fileName);
}

void TextFile::clear(std::string fileName)
{
	//не работает
}

//TextFile::TextFile() :
//		fileName(""), fullPath(""), fileCopy()
//{
//}

TextFile::TextFile(std::string fileName) :
		fileName(fileName), fullPath(""), fileCopy()
{
}

TextFile::~TextFile()
{
}

void TextFile::setName(std::string fileName)
{
	std::string fullPath = std::string("");
	if (PathList::getSingletonPtr()->getPath(fileName, fullPath))
	{
		this->fileName = fileName;
		std::fstream m_stream;
		m_stream.open(fileName.c_str());
		m_stream.close();
	}
	else
	{

	}
}

void TextFile::write(std::string text)
{
	write(text, this->fileName);
	return;
}

void TextFile::copyByStrokes()
{
	std::string line;
	std::ifstream m_file(this->fileName.c_str());
	if (m_file.is_open())
	{
		while (getline(m_file, line))
		{
			this->fileCopy.push_back(line);
		}
		m_file.close();
		line.clear();
	}
	else
		throw Exception("I can't open file" + this->fileName);
}

void TextFile::copyByStrokes(std::string fileName)
{
	std::string line;
	std::ifstream m_file(fileName.c_str());
	if (m_file.is_open())
	{
		while (getline(m_file, line))
		{
			this->fileCopy.push_back(line);
		}
		m_file.close();
		line.clear();
	}
	else
		throw Exception("I can't open file" + fileName);
}

//void TextFile::copyByWords(std::string fileName) {
//	std::string line;
//	std::ifstream m_file(fileName.c_str());
//	if (m_file.is_open()) {
//		while (getline(m_file, line)) {
//			std::istringstream ist(line);
//			std::string tmp;
//			while (ist >> tmp) {
//				fileCopy.push_back(tmp);
//			}
//		}
//		m_file.close();
//		line.clear();
//	}
//
//	else
//		throw Exception("I Can't open file" + fileName);
//}
//
//void TextFile::copyByWords() {
//	copyByWords(this->fileName);
//	return;
//}

void TextFile::clear()
{
	clear(this->fileName);
}

void TextFile::print()
{
//	std::vector<std::string>::const_iterator it = fileCopy.begin();
	for (auto it = fileCopy.begin(); it != fileCopy.end(); it++)
		std::cout << *(it) << " ";
}

template<class T> std::string atos(T real)
{
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
	return str;
}

} /* namespace Core */
