/* rodata_0x43214: const pointer table, 5 x uint32 (2 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x43214, 20 bytes. Reader(s): FUN_000431c0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x43214[5] = {
    0x2000230c,
    0x20007554,
    0x000aae0f,
    0x000aa86c,
    0x000aa891,
};
