/* rodata_0x48974: const pointer table, 9 x uint32 (3 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x48974, 36 bytes. Reader(s): FUN_000488bc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x48974[9] = {
    0x2000392c,
    0x000ef6f2,
    0x000ef058,
    0x2000230c,
    0x20007554,
    0x000ef506,
    0x000ef4fa,
    0x000ef519,
    0x000ef553,
};
