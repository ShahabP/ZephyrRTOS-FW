#include "fhr_sim.h"
#include <stdlib.h>

/* Generate a simple pseudo-random fetal heart rate between 140 and 160 bpm */
uint16_t fhr_sim_generate(void)
{
    /* rand() modulo 21 gives 0..20 -> +140 -> 140..160 */
    return (uint16_t)(140 + (rand() % 21));
}
