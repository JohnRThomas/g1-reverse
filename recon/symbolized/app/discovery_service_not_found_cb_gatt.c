#include "g1_app_symbols.h"
/* named: discovery_service_not_found_cb_gatt */
/* Reconstructed discovery_service_not_found_cb_gatt @ 0x18a1c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt);
extern void gatt_discover(unsigned int a, unsigned int b);

void discovery_service_not_found_cb_gatt(unsigned int param_1)
{
    DEBUG_PRINT("GATT Service could not be found during the discovery\n" /*=0x9a8c3*/);
    gatt_discover(param_1, 0);
}

