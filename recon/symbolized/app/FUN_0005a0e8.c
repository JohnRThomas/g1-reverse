#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a0e8 @ 0x0005a0e8
 * public-name: FUN_0005a0e8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f47d7                             @ 0x000f47d7
 */
/* Reconstructed internal function FUN_0005a0e8 @ 0x5a0e8.
 * Reachable code is [0x5a0e8,0x5a120), 56 bytes.  Its two-word literal pool
 * occupies [0x5a120,0x5a128), immediately before FUN_0005a128. */
#include <stdint.h>

extern void *FUN_00053008(unsigned type, const void *identity,
                          const void *range, unsigned count);
extern void FUN_00082a42(uint32_t module, uint32_t level, const void *record);

struct error_record {
    uint32_t count;
    uint32_t message;
    uint32_t detail;
};

void FUN_0005a0e8(unsigned char *entry)
{
    void *detail = FUN_00053008(entry[0], entry + 1, entry + 8, 4);
    if (detail != 0) {
        const struct error_record record = {
            .count = 3,
            .message = ((unsigned long)&rodata_f47d7) /*=0xf47d7*/,
            .detail = (uint32_t)(uintptr_t)detail,
        };
        FUN_00082a42(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &record);
    }
}
