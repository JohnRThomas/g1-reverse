/* Reconstructed k_uptime_get_5 @ 0x0007d2d8 from Zephyr kernel.h.
 * Raw backmap: FUN_0007d2d8@0x0007d2d8. */

#include <stdint.h>
extern uint64_t uptime_ticks_get(void); /* FUN_00086698@0x00086698 */
int64_t k_uptime_get_5(void){ return (int64_t)((uptime_ticks_get()*UINT64_C(1000))>>15); }
