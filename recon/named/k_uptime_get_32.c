/* readable reconstruction; identity: FUN_0007c0c8 @ 0x0007c0c8
 * public-name: k_uptime_get_32
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_32 @ 0x0007c0c8 from Zephyr kernel.h.
 * Raw backmap: FUN_0007c0c8@0x0007c0c8. */

#include <stdint.h>
extern uint64_t uptime_ticks_get(void); /* FUN_00086698@0x00086698 */
uint32_t k_uptime_get_32(void){ return (uint32_t)((uptime_ticks_get()*UINT64_C(1000))>>15); }
