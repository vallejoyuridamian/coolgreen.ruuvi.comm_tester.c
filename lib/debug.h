/*
 * debug.h
 *
 *  Created on: Apr 26, 2019
 *      Author: user
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <linux/types.h>
#include <stdio.h>

#define UPDATE_DEBUG_MODE 0

#if (UPDATE_DEBUG_MODE == 1)
    #define print_dbgmsg(str, args...)	\
        fprintf(stderr,"%s: " str, __func__, ##args)
    #define print_dbgmsgnofunc(str, args...)	\
        fprintf(stderr,"" str, ##args)
#else
    #define print_dbgmsg(str, args...)
    #define print_dbgmsgnofunc(str, args...)
#endif

#define print_logmsg(str, args...) \
    fprintf(stderr,"%s: " str, __func__, ##args)
#define print_logmsgnofunc(str, args...) \
    fprintf(stderr,"" str, ##args)
#define print_errmsg(str, args...) \
	fprintf(stderr,"%s: " str, __func__, ##args)

#endif /* DEBUG_H */
