#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c176 @ 0x0007c176
 * public-name: device_info_set_bytes_cc_ce
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   device_info_set_bytes_cc_ce              <= FUN_0007c176 @ 0x0007c176
 */
/* Reconstructed FUN_0007c176 @ 0x7c176  (parity: 300/300 trials, PROVEN) */

extern char *get_device_info(void);
void device_info_set_bytes_cc_ce(unsigned char param_1, unsigned char param_2) {
    char *p1 = get_device_info();
    *(volatile unsigned char*)(p1 + 0xce) = param_2;
    char *p2 = get_device_info();
    *(volatile unsigned char*)(p2 + 0xcc) = param_1;
}
