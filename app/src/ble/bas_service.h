#ifndef BAS_SERVICE_H
#define BAS_SERVICE_H

#include <zephyr/types.h>

void bas_init(void);
void bas_set_level(uint8_t level);
void bas_notify_level(void);

#endif
