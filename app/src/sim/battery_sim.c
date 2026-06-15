#include "battery_sim.h"

static int level = 100;

uint8_t battery_sim_get(void)
{
    if (level < 0) {
        level = 0;
    }
    return (uint8_t)level;
}

uint8_t battery_sim_decrease(void)
{
    if (level > 0) {
        level--;
    }
    return battery_sim_get();
}
