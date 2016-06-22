#include "Library.hpp"

#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include "Exception.h"
#include "PathList.hpp"

//using namespace Core;

namespace Core {

static Library singletonManager;

//static const std::string errorType =
//		"Executing error: can't identify VAR type: ";
//static const std::string errorTypeOperation =
//		"Wrong operation: type is not supported";
//static const std::string errorUnknownVariable = "Unknown variable";
static const std::string errorConvert = "Can't convert to: ";

#define ERREND throw Exception( errorEnding+currentFileName+";\n");
#define ERRTYPE throw Exception( errorType+"file: "+currentFileName+"; string:"+atos(currentString)+";\n");
#define ERRFLAG throw Exception( errorFlag+atos(currentString)+"file: "+currentFileName+";\n");
#define ERROPERATION throw Exception( errorTypeOperation+";\n");
#define ERRPARAM throw Exception( errorUnknownVariable+"\n;");
#define ERRHEAD throw Exception( errorHead+currentFileName+";\n");
#define ERRCONVERT throw Exception(errorConvert+str);
#define IN std::cin>>
#define OUT std::cout<<
#define IGNORE ;

template<class T> std::string atos(T real) {
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
	return str;
}

bool stob(std::string str) {
	if (str == "true" || str == "TRUE" || str == "1")
		return true;
	else if (str == "false" || str == "FALSE" || str == "0")
		return false;
	else
		ERRCONVERT
}

Library::Library() {
	currentString = 1;
}

Library::~Library() {
}

Library Library::getSingleton() {
	return singletonManager;
}

Library* Library::getSingletonPtr() {
	return &singletonManager;
}

std::string Library::getParam(std::string param) {
	return table.at(param);
}

void Library::loadConfigFile(std::string fileName) {
	currentFileName = fileName;
	//scriptCopy.clear();
//	scriptCopy.copyByStrokes(fileName);
	copyByStrokes(fileName);
//	auto it = scriptCopy.fileCopy.begin(),
//			end = scriptCopy.fileCopy.end();
//	for (; it != end; ++it) {
//		configStroke(*(it));
	auto it = this->fileCopy.begin(),
			end = this->fileCopy.end();
	for (; it != end; ++it) {
		configStroke(*(it));
		currentString++;
	}
}

void Library::addParam(std::string x, std::string y) {
	table.insert(std::make_pair(x, y));
}

void Library::configStroke(std::string stroke) {
	std::istringstream ist(stroke);
	std::string head = "", x = "", y = "", z = "", add = currentSpace
			+ currentClaster;
	ist >> head;
	if (stroke.empty() == true)
		return;
	else if (head[0] == '#')
		return;
	else if (head == "path" || head == "PATH") {
		ist >> x;
		PathList::getSingletonPtr()->addPath(x);
	}

	else if (head == ":") {
		ist >> x;
		ist >> y;
		table.insert(std::make_pair(x, y));
	}
}

void Library::clear() {
//	scriptCopy.clear();
	this->fileCopy.clear ();
	table.clear();
}

void Library::printAllPaths() {
	PathList::getSingletonPtr()->print();
}

void Library::printAll() {
	for (auto it = table.begin(); it != table.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}

} /* namespace Core */
