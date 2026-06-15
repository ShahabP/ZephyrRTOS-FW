#include <zephyr/ztest.h>
#include "../app/src/sim/battery_sim.h"

ZTEST(battery_tests, test_battery_never_negative)
{
    for (int i = 0; i < 200; ++i) {
        uint8_t v = battery_sim_decrease();
        zassert_true(v <= 100, "Battery above 100: %u", v);
    }
    uint8_t v = battery_sim_get();
    zassert_true(v == 0, "Battery should reach 0, got %u", v);
}

ZTEST_SUITE(battery_tests, NULL, NULL, NULL, NULL, NULL);
