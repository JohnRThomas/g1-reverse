#include "g1_app_symbols.h"
/* named: fuel_gauge_update */
/* Reconstructed fuel_gauge_update @ 0x10b18  (parity: 50/50 trials, PROVEN) */
extern int fuel_gauge_poll_should_stop(void);
int fuel_gauge_update(unsigned int param_1)
{
    int iVar8 = fuel_gauge_poll_should_stop();
    if (iVar8 == 0) return -1;
    return 0;
}

