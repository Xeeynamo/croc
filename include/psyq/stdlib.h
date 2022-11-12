/*
 * File:stdlib.h
 */
/*
 * $PSLibId$
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <abs.h>
#include <convert.h>
#include <malloc.h>
#include <qsort.h>
#include <rand.h>
#include <stddef.h>

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) ||                  \
    defined(c_plusplus)
extern "C" {
#endif

extern void* bsearch(unsigned char*, unsigned char*, size_t, size_t, int (*)());
extern void exit();

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) ||                  \
    defined(c_plusplus)
}
#endif

#endif /* _STDLIB_H */
