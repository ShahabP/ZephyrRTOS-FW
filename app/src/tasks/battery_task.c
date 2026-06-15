#include <zephyr.h>
#include <sys/printk.h>
#include "battery_task.h"
#include "../ble/bas_service.h"
#include "../sim/battery_sim.h"

void battery_thread(void)
{
    while (1) {
        k_sleep(K_SECONDS(60));
        uint8_t level = battery_sim_decrease();
        bas_set_level(level);
        bas_notify_level();
        printk("Battery level: %u%%\n", level);
    }
}

K_THREAD_DEFINE(battery_thread_id, 1024, battery_thread, NULL, NULL, NULL, 7, 0, 0);
