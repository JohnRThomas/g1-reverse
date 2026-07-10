/* named: discovery_service_not_found_cb_gatt */
/* Reconstructed discovery_service_not_found_cb_gatt @ 0x18a1c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt);
extern void gatt_discover(unsigned int a, unsigned int b);

void discovery_service_not_found_cb_gatt(unsigned int param_1)
{
    DEBUG_PRINT(0x9a8c3U);
    gatt_discover(param_1, 0);
}

