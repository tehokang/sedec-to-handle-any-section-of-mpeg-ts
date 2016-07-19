#ifndef __COMMON__THKANG2___
#define __COMMON__THKANG2___

#include <stdio.h>
//#define SECTION_DEBUG	printf
#define SECTION_DEBUG(fmt, ...) \
    do { \
        printf("\033[37;32m"); \
        printf("[%-20s]", __FUNCTION__); \
        printf ( fmt, ##__VA_ARGS__); \
        printf("\033[0m"); \
    } while(0)

#endif

