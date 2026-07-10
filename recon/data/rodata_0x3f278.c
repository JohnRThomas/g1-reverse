/* rodata_0x3f278: const pointer table, 12 x uint32 (5 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x3f278, 48 bytes. Reader(s): FUN_0003e7f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3f278[12] = {
    0x000a9fcd,
    0x000a9fe6,
    0x000a9ff7,
    0x000aa01a,
    0x2000230c,
    0x20007554,
    0x000aa425,
    0x000a9f93,
    0x000a9eff,
    0x2001ba2e,
    0x20007574,
    0x20015e52,
};
