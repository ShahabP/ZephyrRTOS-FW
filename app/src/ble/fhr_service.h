#ifndef FHR_SERVICE_H
#define FHR_SERVICE_H

#include <zephyr/types.h>
#include <stdbool.h>

void fhr_init(void);
void fhr_notify_measure(uint16_t bpm);
void fhr_set_streaming(bool enabled);
bool fhr_is_streaming(void);

#endif
