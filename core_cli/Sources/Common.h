/*
 * define.h
 *
 *  Created on: Jun 10, 2016
 *      Author: avs
 */

#ifndef _common_h_
#define _common_h_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>

//#undef DEBUG

#define DEBUG_IO

#ifdef _WIN32
#define TMPDIR "./tmp/"
#else
#define TMPDIR "/tmp/"
#endif

#define DUMMY 999.99f


#ifdef DEBUG
#define ENABLE_RUNTIME
#define ENABLE_LOG2FILE
#endif

#endif

