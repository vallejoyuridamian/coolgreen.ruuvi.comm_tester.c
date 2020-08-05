/*
 * api.h
 *
 *  Created on: Apr 26, 2019
 *      Author: user
 */

#ifndef API_H_
#define API_H_

#include <linux/types.h>
/***USER_FUNCTIONS**/
/*start*/
__s8 api_process(void);
__s8 api_send_fltr_id(__u32 cmd, __u16 id);
__s8 api_send_bool_payload(__u32 cmd, __u8 state);
__s8 api_send_all(__u32 cmd,
                  __u16 fltr_id,
                  __u8 fltr_tags_state,
                  __u8 coded_phy_state,
                  __u8 ext_payload_state,
                  __u8 scan_phy_state,
                  __u8 ch_37_state,
                  __u8 ch_38_state,
                  __u8 ch_39_state);
/*end*/

#endif /* API_H_ */
