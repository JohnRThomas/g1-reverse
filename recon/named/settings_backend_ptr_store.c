/* named: settings_backend_ptr_store */
/* globals referenced:
//   0x2000a100  g_settings_nvs_backend       
*/
/* Reconstructed settings_backend_ptr_store @ 0x4e3dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void settings_backend_ptr_store(uint32_t param_1) {
    *(volatile uint32_t*)0x2000a100UL = param_1;
}

