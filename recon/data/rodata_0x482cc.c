/* rodata_0x482cc: const pointer table, 12 x uint32 (6 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x482cc, 48 bytes. Reader(s): FUN_00047c48
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x482cc[12] = {
    0x2001d264,
    0x2000a080,
    0x2001d34b,
    0x2000a078,
    0x2001d34a,
    0x20007554,
    0x000ef76f,
    0x0009ea0a,
    0x000ef0fb,
    0x000ef2df,
    0x000ef214,
    0x000ef2fc,
};
