/*
 * define.h
 *
 *  Created on: Jun 10, 2016
 *      Author: avs
 */

#ifndef _common_h_
#define _common_h_

#include "Uncopy.h"
#include "Exception.h"
#include "Log.h"

#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

#ifdef DEBUG
	#define ENABLE_RUNTIME
	#define ENABLE_LOG2FILE
#endif

//#ifdef STD11
	#include <chrono>
//#endif
//#ifdef std=c++11
//#endif
//namespace Core {
//typedef std::string string;
//typedef std::vector<std::string> vector;

//}
#endif


