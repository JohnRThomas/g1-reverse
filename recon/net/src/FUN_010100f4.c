/* net-core FUN_010100f4 @ 0x10100f4  (CFG-directed candidate) */
/* net-core FUN_010100f4 @ 0x010100f4
 * Readable role: sample the controller timing pair and store its masked fields.
 * Address back-map: controller_timing_sample = FUN_0101f8cc @ 0x0101f8cc.
 */
#include <stdint.h>

extern uint64_t FUN_0101f8cc(void);
#define controller_timing_sample FUN_0101f8cc

void FUN_010100f4(void *output)
{
    uint64_t sample = controller_timing_sample();

    *(uint32_t *)((uint8_t *)output + 8) =
        (uint32_t)(sample >> 32) & 0x1807U;
    *(uint32_t *)((uint8_t *)output + 4) =
        (uint32_t)sample & 0xf704492fU;
}
