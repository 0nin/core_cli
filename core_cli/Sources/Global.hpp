#ifndef _global_h_
#define _global_h_

#if defined __WIN32__ || _WIN32 && defined _MSC_VER
#define PLATFORM WIN32_VISUAL
#else
#define PLATFORM UNIX
#endif

#include "Common.hpp"

//extern int _main(int argc, char* args[]);

#endif
