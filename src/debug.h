/**
 * Debug helper.
 * Defines functions to show log
 *
 * License: BSD-3
 * Author: Oleg Protasevich
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <linux/types.h>
#include <stdio.h>

#define UPDATE_DEBUG_MODE 0
#if (UPDATE_DEBUG_MODE == 1)
    #define print_dbgmsg(str, ...)	\
        fprintf(stderr,"%s: " str, __func__, ##__VA_ARGS__)
    #define print_dbgmsgnoarg(str)	\
        fprintf(stderr,"%s in %s: ",str, __func__)
    #define print_dbgmsgnofunc(str, ...)	\
        fprintf(stderr,"" str, ##__VA_ARGS__)
    #define print_dbgmsgnofuncnoarg(str)	\
        fprintf(stderr,"%s", str)
#else
    #define print_dbgmsg(str, ...)
    #define print_dbgmsgnoarg(str)
    #define print_dbgmsgnofunc(str, ...)
    #define print_dbgmsgnofuncnoarg(str)
#endif

#define print_logmsg(str, ...) \
    fprintf(stderr,"%s: " str, __func__, ##__VA_ARGS__)
#define print_logmsgnoarg(str)	\
    fprintf(stderr,"%s in %s: ",str, __func__)
#define print_logmsgnofunc(str, ...) \
    fprintf(stderr,"" str, ##__VA_ARGS__)
#define print_logmsgnofuncnoarg(str)	\
    fprintf(stderr,"%s", str)
#define print_errmsg(str, ...) \
    fprintf(stderr,"%s: " str, __func__, ##__VA_ARGS__)
#define print_errmsgnoarg(str)	\
    fprintf(stderr,"%s in %s: ",str, __func__)
#define print_errmsgnofunc(str, ...) \
    fprintf(stderr,"" str, ##__VA_ARGS__)
#define print_errmsgnofuncnoarg(str)	\
    fprintf(stderr,"%s", str)
#endif /* DEBUG_H */
