/* readable reconstruction; identity: FUN_00071678 @ 0x00071678
 * public-name: __errno_location
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __errno_location                         <= FUN_00071678 @ 0x00071678
 * address symbols (name @ address):
 *   g_current_thread_ptr                     @ 0x2000b450
 */
/* Reconstructed FUN_00071678 @ 0x71678  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int __errno_location(void)
{
    return *(volatile int32_t*)0x2000b450UL + 0x78;
}
