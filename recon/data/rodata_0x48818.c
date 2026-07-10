/* rodata_0x48818: const pointer table, 10 x uint32 (3 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x48818, 40 bytes. Reader(s): FUN_00047c48
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x48818[10] = {
    0x20007554,
    0x000ef76f,
    0x000a125e,
    0x000ef472,
    0x20011d81,
    0x000ef0fb,
    0x000a1027,
    0x000a116d,
    0x20007b38,
    0x000ef4b1,
};
