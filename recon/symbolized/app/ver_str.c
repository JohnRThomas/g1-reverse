#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053344 @ 0x00053344
 * public-name: ver_str
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_88480                             @ 0x00088480
 *   rodata_ef596                             @ 0x000ef596
 */
/* Reconstructed ver_str @ 0x53344  (CFG-directed candidate) */
/* Owner: NCS 2.5.1 Bluetooth host hci_core.c; raw backmap FUN_00053344@0x00053344. */
#include <stdint.h>
const char *ver_str(uint32_t version)
{
    const uint32_t *version_strings = (const uint32_t *)((unsigned long)&rodata_88480) /*=0x88480*/;
    if (version < 14u) {
        return (const char *)(uintptr_t)version_strings[version];
    }
    return (const char *)((unsigned long)&rodata_ef596) /*=0xef596*/;
}
