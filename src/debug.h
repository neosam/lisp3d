#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

#ifdef NDEBUG
#define DMSG(msg) printf(msg)
#else
#define DMSG(msg)
#endif

#endif
