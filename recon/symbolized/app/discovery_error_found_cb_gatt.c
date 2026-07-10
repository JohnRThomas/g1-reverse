#include "g1_app_symbols.h"
/* named: discovery_error_found_cb_gatt */
/* Reconstructed discovery_error_found_cb_gatt @ 0x18894  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt);
extern void gatt_discover(unsigned int a, unsigned int b);

void discovery_error_found_cb_gatt(unsigned int param_1)
{
    DEBUG_PRINT("The discovery procedure for GATT Service failed, err %d\n" /*=0x9a688*/);
    gatt_discover(param_1, 0);
}

