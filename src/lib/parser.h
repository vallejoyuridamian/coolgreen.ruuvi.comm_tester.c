/**
 * Parser helper.
 * Parse incomming data from linux terminal
 *
 * License: BSD-3
 * Author: Oleg Protasevich
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <linux/types.h>

/***USER_FUNCTIONS***/
/*start*/
int parse_callbacks_unreg(void);
int parse_callbacks_reg(void* p_callback);
int parse(__u8 *buffer);
/*end*/

#endif /* PARSER_H_ */

