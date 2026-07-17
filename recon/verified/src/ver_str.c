/* Reconstructed ver_str @ 0x53344  (CFG-directed candidate) */
/* Owner: NCS 2.5.1 Bluetooth host hci_core.c; raw backmap FUN_00053344@0x00053344. */
#include <stdint.h>
const char *ver_str(uint32_t version)
{
    const uint32_t *version_strings = (const uint32_t *)0x00088480u;
    if (version < 14u) {
        return (const char *)(uintptr_t)version_strings[version];
    }
    return (const char *)0x000ef596u;
}
