/**
 * Parser helper.
 * Parse incomming data from linux terminal
 *
 * License: BSD-3
 * Author: Oleg Protasevich
 */

#ifndef DBUSCONTROLLER_H_
#define DBUSCONTROLLER_H_

#ifndef RUUVI_ESP
#include <linux/types.h>
#include <stdbool.h>
#else
#include "ruuvi_gateway.h"
#endif

int
dbus_connect(bool new);
void
dbus_check_new_messages(void);

#endif /* DBUSCONTROLLER_H_ */
