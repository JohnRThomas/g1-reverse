#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00058bfc @ 0x00058bfc
 * public-name: FUN_00058bfc
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   ADDR_att_timeout_THUMB                   @ 0x00059921
 */
/* Reconstructed FUN_00058bfc @ 0x58bfc */
#include <stdint.h>

extern void FUN_00081c22(void *object);
extern void FUN_000732d4(void *object, uint32_t event);
extern void ext5c6c8(void *object);

void FUN_00058bfc(void **context)
{
    volatile uint32_t *flags =
        (volatile uint32_t *)((uint8_t *)context + 0x118);
    __atomic_fetch_or(flags, UINT32_C(4), __ATOMIC_ACQ_REL);
    FUN_00081c22((uint8_t *)context - 8);
    FUN_000732d4((uint8_t *)context + 0x158, UINT32_C(0x00059921));
    ext5c6c8(*context);
}
