/*
 * This file contains some helper functions for c.
 */

#ifndef MISC_H
#define MISC_H

/*
 * Memory allocation
 */
#define MALLOC(t) (t*)malloc(sizeof(t))
#define MALLOCN(t, n) (t*)malloc(sizeof(t) * n)
#define REALLOC(t, ptr) (t*)realloc(ptr, sizeof(t))
#define REALLOCN(t, ptr, n) (t*)realloc(ptr, sizeof(t) * n)

#endif
