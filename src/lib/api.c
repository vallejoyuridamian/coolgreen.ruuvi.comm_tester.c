#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/***USER_INCLUDES***/
/*start*/
#include "types_def.h"
#include "debug.h"
#include "terminal.h"
#include "parser.h"
#include "time.h"
#include "formated_output.h"
#include "dbuscontroller.h"
#include "ruuvi_endpoint_ca_uart.h"
#ifdef RUUVI_ESP
#include "adv_post.h"
#endif
/*end*/

/***USER_DEFINES***/
/*start*/
#define BUFFER_PAYLOAD_SIZE 204
/*end*/

/***USER_TYPES**/
/*start*/
/*end*/

/***USER_STATIC_FUNCTIONS**/
/*start*/
static int
api_ack_callback(const uint8_t *const buffer);
static int
api_id_callback(const uint8_t *const buffer);
static int
api_report_callback(const uint8_t *const buffer);
/*end*/

/***USER_VARIABLES***/
/*start*/
api_callbacks_fn_t parser_callback_func_tbl = {
    .ApiAckCallback    = api_ack_callback,
    .ApiReportCallback = api_report_callback,
    .ApiIdCallback     = api_id_callback,
};

adv_callbacks_fn_t adv_callback_func_tbl_null = {
    .AdvAckCallback    = NULL,
    .AdvReportCallback = NULL,
    .AdvReportCallback = NULL,
};

adv_callbacks_fn_t *p_adv_callback_func_tbl = &adv_callback_func_tbl_null;

__u8 report_state = 0;

/*end*/

__s8
api_send_bool_payload(__u32 cmd, __u8 state)
{
    int8_t               res          = 0;
    re_ca_uart_payload_t uart_payload = { 0 };
    uint8_t              data[BUFFER_PAYLOAD_SIZE];
    uint8_t              data_length;

    print_dbgmsgnoarg("Enter\n");

    uart_payload.cmd = (re_ca_uart_cmd_t)cmd;
    if ((bool)state == true)
    {
        uart_payload.params.bool_param.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.bool_param.state = RE_CA_BOOL_DISABLE;
    }
    data_length = sizeof(data);

    if (RE_SUCCESS != re_ca_uart_encode(data, &data_length, &uart_payload))
    {
        res = (-1);
    }
    else
    {
        terminal_send_msg((uint8_t *)data, data_length);
#ifndef RUUVI_ESP
        dbus_check_new_messages();
#endif
    }
    print_dbgmsgnoarg("End\n");
    return (__s8)res;
}

__s8
api_send_get_device_id(__u32 cmd)
{
    int8_t               res          = 0;
    re_ca_uart_payload_t uart_payload = { 0 };
    uint8_t              data[BUFFER_PAYLOAD_SIZE];
    uint8_t              data_length;

    print_dbgmsgnoarg("Enter\n");
    uart_payload.cmd = (re_ca_uart_cmd_t)cmd;
    data_length      = sizeof(data);

    if (RE_SUCCESS != re_ca_uart_encode(data, &data_length, &uart_payload))
    {
        res = (-1);
    }
    else
    {
        terminal_send_msg((uint8_t *)data, data_length);
#ifndef RUUVI_ESP
        dbus_check_new_messages();
#endif
    }
    print_dbgmsgnoarg("End\n");
    return (__s8)res;
}

__s8
api_send_fltr_id(__u32 cmd, __u16 id)
{
    int8_t               res          = 0;
    re_ca_uart_payload_t uart_payload = { 0 };
    uint8_t              data[BUFFER_PAYLOAD_SIZE];
    uint8_t              data_length;

    print_dbgmsgnoarg("Enter\n");

    uart_payload.cmd = (re_ca_uart_cmd_t)cmd;
    data_length      = sizeof(data);

    if (RE_SUCCESS != re_ca_uart_encode(data, &data_length, &uart_payload))
    {
        res = (-1);
    }
    else
    {
        terminal_send_msg((uint8_t *)data, data_length);
#ifndef RUUVI_ESP
        dbus_check_new_messages();
#endif
    }
    print_dbgmsgnoarg("End\n");
    return (__s8)res;
}

__s8
api_send_all(
    __u32 cmd,
    __u16 fltr_id,
    __u8  fltr_tags_state,
    __u8  coded_phy_state,
    __u8  ext_payload_state,
    __u8  scan_phy_state,
    __u8  ch_37_state,
    __u8  ch_38_state,
    __u8  ch_39_state)
{
    int8_t               res          = 0;
    re_ca_uart_payload_t uart_payload = { 0 };
    uint8_t              data[BUFFER_PAYLOAD_SIZE];
    uint8_t              data_length;

    print_dbgmsgnoarg("Enter\n");

    uart_payload.cmd                          = (re_ca_uart_cmd_t)cmd;
    uart_payload.params.all_params.fltr_id.id = fltr_id;

    if ((bool)fltr_tags_state == true)
    {
        uart_payload.params.all_params.bools.fltr_tags.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.fltr_tags.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)coded_phy_state == true)
    {
        uart_payload.params.all_params.bools.coded_phy.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.coded_phy.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)ext_payload_state == true)
    {
        uart_payload.params.all_params.bools.ext_payload.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.ext_payload.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)scan_phy_state == true)
    {
        uart_payload.params.all_params.bools.scan_phy.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.scan_phy.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)ch_37_state == true)
    {
        uart_payload.params.all_params.bools.ch_37.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.ch_37.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)ch_38_state == true)
    {
        uart_payload.params.all_params.bools.ch_38.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.ch_38.state = RE_CA_BOOL_DISABLE;
    }

    if ((bool)ch_39_state == true)
    {
        uart_payload.params.all_params.bools.ch_39.state = RE_CA_BOOL_ENABLE;
    }
    else
    {
        uart_payload.params.all_params.bools.ch_39.state = RE_CA_BOOL_DISABLE;
    }

    data_length = sizeof(data);

    if (RE_SUCCESS != re_ca_uart_encode(data, &data_length, &uart_payload))
    {
        res = (-1);
    }
    else
    {
        terminal_send_msg((uint8_t *)data, data_length);
#ifndef RUUVI_ESP
        dbus_check_new_messages();
#endif
    }
    print_dbgmsgnoarg("End\n");
    return (__s8)res;
}

/***USER_CALLBACKS**/
/*start*/
static int
api_ack_callback(const __u8 *const buffer)
{
    int                  res          = -1;
    re_ca_uart_payload_t uart_payload = { 0 };

    if (RE_SUCCESS == re_ca_uart_decode((uint8_t *)buffer, &uart_payload))
    {
        res = 0;
        if (NULL != p_adv_callback_func_tbl->AdvAckCallback)
        {
            p_adv_callback_func_tbl->AdvAckCallback((void *)&uart_payload);
        }
        formated_output_ack((void *)&uart_payload);
    }
    return res;
}

static int
api_id_callback(const __u8 *const buffer)
{
    int                  res          = -1;
    re_ca_uart_payload_t uart_payload = { 0 };

    if (RE_SUCCESS == re_ca_uart_decode((uint8_t *)buffer, &uart_payload))
    {
        res = 0;
        if (NULL != p_adv_callback_func_tbl->AdvIdCallback)
        {
            p_adv_callback_func_tbl->AdvIdCallback((void *)&uart_payload);
        }
        formated_output_device_id((void *)&uart_payload);
    }
    return res;
}

static int
api_report_callback(const __u8 *const buffer)
{
    int                  res          = -1;
    re_ca_uart_payload_t uart_payload = { 0 };
    if (RE_SUCCESS == re_ca_uart_decode((uint8_t *)buffer, &uart_payload))
    {
        res = 0;
        if (NULL != p_adv_callback_func_tbl->AdvReportCallback)
        {
            p_adv_callback_func_tbl->AdvReportCallback((void *)&uart_payload);
        }
        if (!report_state)
        {
            formated_output_report((void *)&uart_payload);
        }
    }
    return res;
}

/*end*/

__s8
api_process(__u8 state)
{
    print_dbgmsgnoarg("Enter\n");
    report_state = state;
    parse_callbacks_reg((void *)&parser_callback_func_tbl);
#ifndef RUUVI_ESP
    while (1)
    {
    }
    parse_callbacks_unreg();
#endif
    print_dbgmsgnoarg("End\n");
    return 0;
}

int
api_callbacks_reg(void *p_callback)
{
    int res = 0;
    print_dbgmsgnoarg("Enter\n");
    if ((adv_callbacks_fn_t *)p_callback != NULL)
    {
        p_adv_callback_func_tbl = (adv_callbacks_fn_t *)p_callback;
    }
    else
    {
        print_errmsgnofuncnoarg("Nullptr\n");
        res = (-1);
    }
    print_dbgmsgnoarg("End\n");
    return res;
}

int
api_callbacks_unreg()
{
    print_dbgmsgnoarg("Enter\n");
    p_adv_callback_func_tbl = &adv_callback_func_tbl_null;
    print_dbgmsgnoarg("End\n");
    return 0;
}
