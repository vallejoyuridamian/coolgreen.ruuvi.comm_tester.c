/**
 * Terminal helper.
 * Defines some params to use linux terminal.
 *
 * License: BSD-3
 * Author: Oleg Protasevich
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <linux/types.h>

/***USER_DEFINES***/
/*start*/
#define ONE_SYMBOL_DELAY 		1 	//us
#define RX_BUFFER_MAX_SIZE  	4096
#define STEP_RX_TIMEOUT  		1000 //us
#define RX_ASK_TIMEOUT  		5000 //in 1000us
#define DEFAULT_BAUDRATE  		B115200//in 1000us
/*end*/

/**USER FUNCTIONS***/
/*start*/
int terminal_open(char* device_address);
int terminal_close(void);
int terminal_send_msg(__u8 *data,
                      __u8 size);
/*end*/

#endif /* TERMINAL_H_ */

