#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h> 
#include <termios.h>
#include <string.h> 
#include <pthread.h>

/***USER_INCLUDES***/
/*start*/
#include "debug.h"
#include "terminal.h"
#include "parser.h"
/*end*/

/**USER_TYPES***/
/*start*/
#pragma pack(push,1)
typedef struct __terminal_struct{
    pthread_t thread_id;
    pthread_t thread_id_call;
    int size;
    int fd;
    uint8_t rx_buffer[RX_BUFFER_MAX_SIZE];
}terminal_struct_t;
#pragma pack(pop)
/*end*/

/**USER_VARIABLES***/
/*start*/
terminal_struct_t terminal;
/*end*/

static int wait(uint8_t *data, uint32_t timeout);
static int send_msg(uint8_t *data,
                    uint8_t size);

static int send_msg(uint8_t *data,
                    uint8_t size)
{
    print_dbgmsgnofuncnoarg("TX: ");
    for (int i = 0; i < size; i++)
    {
        print_dbgmsgnofunc("0x%02x ",data[i]);//(char*)&data[0]);
    }
    print_dbgmsgnofuncnoarg("\n");
    write(terminal.fd, &data[0], size);
    return 0;
}

static int wait(uint8_t *data_p, uint32_t timeout)
{
	int rx_size=0;
	int rx_size_it; 
    uint8_t data[RX_BUFFER_MAX_SIZE];
    memset(data,0, RX_BUFFER_MAX_SIZE);
    while (terminal.size !=0);
    while(1)
    {
        rx_size_it = read(terminal.fd, &data[rx_size], 1);
        if (rx_size_it <= 0){
        }else{
            rx_size+= rx_size_it;
            for (int i = 0; i < rx_size; i++)
            {
                if ((*(uint8_t*)&data[i]) == 0x12)
                {
                    memcpy(data_p ,data, rx_size);
                    terminal.size = rx_size;
                    rx_size =0;
                    break;
                }
            }
            if ( terminal.size )
            {
                break;
            }
        }
    }
	return 	rx_size;	
}

int terminal_send_msg(__u8 *data,
                      __u8 size)
{
    int res = 0;
    print_dbgmsgnoarg("Enter\n");
    if (send_msg((uint8_t*)data, (uint8_t)size) != 0){
        res = (-1);
	}
    print_dbgmsgnoarg("End\n");
    return res;
}

void *th_ctrl_call(void *vargp)
{
    while (terminal.fd < 0);
    while(1){
        if ( terminal.size )
        {
            print_dbgmsgnofuncnoarg("RX: ");
            for (int i = 0; i < terminal.size; i++)
            {
                print_dbgmsgnofunc("0x%02x ",(*(uint8_t*)&terminal.rx_buffer[i]));//(char*)&data[0]);
            }
            print_dbgmsgnofuncnoarg("\n");
            parse((__u8*)&terminal.rx_buffer[0]);
            terminal.size = 0;
        }
    }
}

void *th_ctrl(void *vargp)
{
    while (terminal.fd < 0);
    while(1){
        wait(terminal.rx_buffer, RX_ASK_TIMEOUT);
    }
}

int terminal_open(char* device_address) {
    print_dbgmsgnoarg("Enter\n");
    memset(&terminal, 0, sizeof(terminal_struct_t));

    terminal.fd = open(device_address, O_RDWR);
    if (terminal.fd < 0){
        return (-1);
    }else{
        struct termios settings;
        speed_t baud = DEFAULT_BAUDRATE;
        tcgetattr(terminal.fd, &settings);
        cfsetospeed(&settings, baud);                   /* baud rate */
        settings.c_cflag &= ~PARENB;                    /* no parity */
        settings.c_cflag &= ~CSTOPB;                    /* 1 stop bit */
        settings.c_cflag &= ~CSIZE;
        settings.c_cflag |= CS8 | CLOCAL;               /* 8 bits */
        settings.c_lflag = ICANON;                      /* canonical mode */
        settings.c_oflag &= ~OPOST;                     /* raw output */

        settings .c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                        | INLCR | IGNCR | ICRNL | IXON);
        settings .c_oflag &= ~OPOST;
        settings .c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        settings .c_cflag &= ~(CSIZE | PARENB);
        settings .c_cflag |= CS8;

        terminal.size = 0;
        tcsetattr(terminal.fd, TCSANOW, &settings); 	/* apply the settings */
        tcflush(terminal.fd, TCOFLUSH);
        pthread_create(&terminal.thread_id, NULL, th_ctrl, NULL);
        pthread_create(&terminal.thread_id_call, NULL, th_ctrl_call, NULL);
    }
    print_dbgmsgnoarg("End\n");
    return 0;
}

int terminal_close(void) {
    print_dbgmsgnoarg("Enter\n");
    close(terminal.fd); /* cleanup */
    print_dbgmsgnoarg("End\n");
    return 0;
}

