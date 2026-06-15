#include <zephyr.h>
#include <sys/printk.h>
#include "fhr_task.h"
#include "../ble/fhr_service.h"
#include "../sim/fhr_sim.h"

void fhr_thread(void)
{
    while (1) {
        k_sleep(K_SECONDS(1));
        uint16_t bpm = fhr_sim_generate();
        if (fhr_is_streaming()) {
            fhr_notify_measure(bpm);
        }
    }
}

K_THREAD_DEFINE(fhr_thread_id, 1024, fhr_thread, NULL, NULL, NULL, 7, 0, 0);
