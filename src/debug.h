#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#include <assert.h>

#ifndef NDEBUG
#define DMSG(msg)                                                    \
	printf("DEBUG %s,%i:", __FILE__, __LINE__);                  \
	printf(msg) 
#else
#define DMSG(msg)
#endif

#endif
