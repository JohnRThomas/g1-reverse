/* readable reconstruction; identity: FUN_00086f92 @ 0x00086f92
 * public-name: FUN_00086f92
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Full reconstruction FUN_00086f92 @ 0x86f92 (36-byte extent). */
#include <stdint.h>

extern int32_t FUN_00078598(uint32_t context, int32_t key);

void FUN_00086f92(uint32_t context, uint8_t *record)
{
    int32_t handle = FUN_00078598(context, *(int16_t *)(record + 0x0e));
    uint16_t flags = *(uint16_t *)(record + 0x0c);

    if (handle == -1) {
        flags &= (uint16_t)~0x1000u;
    } else {
        *(int32_t *)(record + 0x54) = handle;
        flags |= 0x1000u;
    }
    *(uint16_t *)(record + 0x0c) = flags;
}
