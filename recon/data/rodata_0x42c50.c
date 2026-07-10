/* rodata_0x42c50: const pointer table, 15 x uint32 (6 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x42c50, 60 bytes. Reader(s): FUN_00042a64
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x42c50[15] = {
    0x2000230c,
    0x20007554,
    0x000aa778,
    0x000aa611,
    0x20004bf0,
    0x000aa63d,
    0x000aa661,
    0x000aa665,
    0x000aa669,
    0x2001cdcf,
    0x2001cdce,
    0x000aa66d,
    0x2001cdd2,
    0x000aa671,
    0x000aa675,
};
