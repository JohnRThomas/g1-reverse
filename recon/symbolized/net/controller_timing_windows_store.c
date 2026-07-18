#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f198 @ 0x0100f198
 * public-name: controller_timing_windows_store
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_windows_store          <= FUN_0100f198 @ 0x0100f198
 */
/* net-core FUN_0100f198 @ 0x100f198  (CFG-directed candidate) */
/* Role: store the four controller timing-window halfwords. Back-map: FUN_0100f198. */
#include <stdint.h>
void controller_timing_windows_store(void *record, uint16_t window0, uint16_t window1,
                  uint16_t window2, uint16_t window3)
{
    volatile uint16_t *windows = (volatile uint16_t *)((uint8_t *)record + 0x14);
    windows[0] = window0;
    windows[1] = window1;
    windows[2] = window2;
    windows[3] = window3;
}
