#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h> 
#include <termios.h>
#include <string.h> 
#include <signal.h>

/***USER_INCLUDES***/
/*start*/
#include "types_def.h"
#include "terminal.h"
#include "api.h"
#include "debug.h"
/*end*/

#define DEFAULT_DEVICE_COM "/dev/ttyUSB0"
#define CMD_INVALID 255

static void help(void)
{
    print_logmsg("Help:\n");
}

static void signalHandlerShutdown(int sig)
{
    exit(0);
}

/*if (cmd != CMD_INVALID)
{
    switch (cmd) {
    {
        case RE_CA_UART_SET_FLTR_TAGS:
        case RE_CA_UART_SET_CODED_PHY:
        case RE_CA_UART_SET_SCAN_1MB_PHY:
        case RE_CA_UART_SET_EXT_PAYLOAD:
        case RE_CA_UART_SET_CH_37:
        case RE_CA_UART_SET_CH_38:
        case RE_CA_UART_SET_CH_39:
            err_code |= re_ca_uart_encode_bool_payload (buffer, buf_len, payload);
            break;
        case RE_CA_UART_ACK:
            err_code |= re_ca_uart_encode_ack (buffer, buf_len, payload);
            break;
        case RE_CA_UART_SET_FLTR_ID:
            err_code |= re_ca_uart_encode_fltr_id (buffer, buf_len, payload);
            break;
        case RE_CA_UART_SET_ALL:
            state = atoi(argv[i+1],10);
            break;
        default:
            cmd = CMD_INVALID;
            break;
    }

}
*/

int main(int argc, char *argv[])
{
    int res=0;
    int i=0;
    char *deviceCom = DEFAULT_DEVICE_COM;
    int mode=0;
    uint32_t cmd = CMD_INVALID;
    uint32_t payload = CMD_INVALID;
    print_dbgmsg("Enter\n");

    while(i < argc){
        if ((argv[i][0] == '-') && (argv[i+1]) != NULL){
            switch (argv[i][1]){
                case 'D':
                case 'd':
                    deviceCom = argv[i+1];
                    break;
                case 'b':
                case 'B':
                    mode = 1;
                    break;
                case 'c':
                case 'C':
                    //cmd = atoi(argv[i+1],10);
                    break;
                case 'p':
                case 'P':
                    break;
                case 't':
                case 'T':
                    break;
                case 'H':
                case 'h':
                default:
                    help();
                    return (-1);
            }
        }
        i++;
    }

    if (mode)
    {
        daemon(0, 1);
        signal(SIGTERM, signalHandlerShutdown);
        signal(SIGHUP, signalHandlerShutdown);
        signal(SIGUSR1, signalHandlerShutdown);
        signal(SIGQUIT, signalHandlerShutdown);
        signal(SIGINT, signalHandlerShutdown);
        signal(SIGKILL, signalHandlerShutdown);

        if (terminal_open(deviceCom) == 0){
            res = api_process();
            terminal_close();
        }else{
            print_errmsg("No device\n");
            res = (-1);
        }
    }
    else
    {
        if (terminal_open(deviceCom) == 0){
            res = api_send_bool_payload(5, 1);
            terminal_close();
        }else{
            print_errmsg("No device\n");
            res = (-1);
        }

    }
    print_dbgmsg("End\n");
    return res;
}
