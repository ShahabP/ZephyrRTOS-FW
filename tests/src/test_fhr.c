#include <zephyr/ztest.h>
#include "../app/src/sim/fhr_sim.h"

ZTEST(fhr_tests, test_fhr_range)
{
    for (int i = 0; i < 100; ++i) {
        uint16_t v = fhr_sim_generate();
        zassert_true(v >= 140 && v <= 160, "FHR out of range: %u", v);
    }
}

ZTEST_SUITE(fhr_tests, NULL, NULL, NULL, NULL, NULL);
