/*
 * terminal.h
 *
 *  Created on: Apr 26, 2019
 *      Author: user
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <linux/types.h>

/***USER_DEFINES***/
/*start*/
#define ONE_SYMBOL_DELAY 		1 	//us
#define RX_BUFFER_MAX_SIZE  	1024
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
//int terminal_send_msg(uint8_t *data,
//                      uint8_t size)
/*end*/

#endif /* TERMINAL_H_ */

