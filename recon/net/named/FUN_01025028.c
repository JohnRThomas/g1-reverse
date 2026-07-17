/* readable reconstruction; identity: FUN_01025028 @ 0x01025028
 * public-name: FUN_01025028
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01025028 @ 0x1025028  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint32_t * const DAT_01025030 = (volatile uint32_t *)0x41011000;
uint32_t FUN_01025028(void) { return *(uint32_t*)((uint8_t*)DAT_01025030 + 0x504); }
