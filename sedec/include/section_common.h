#ifndef __COMMON__THKANG2___
#define __COMMON__THKANG2___

#include <stdio.h>
//#define SECTION_DEBUG	printf
#define SECTION_DEBUG(fmt, ...) \
    do { \
        fprintf(stderr, "\033[37;32m"); \
        fprintf(stderr, "[%-20s]", __FUNCTION__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\033[0m"); \
    } while(0)

#endif

