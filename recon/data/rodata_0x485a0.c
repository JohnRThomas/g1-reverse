/* rodata_0x485a0: const pointer table, 16 x uint32 (5 SRAM ptrs, 11 flash ptrs)
 * app-core VA 0x485a0, 64 bytes. Reader(s): FUN_00047c48
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x485a0[16] = {
    0x20007554,
    0x000ef76f,
    0x000ef338,
    0x00087bf0,
    0x2001d34b,
    0x2001d264,
    0x2001d263,
    0x2001d26a,
    0x000ef377,
    0x000ef07c,
    0x000ef077,
    0x000ef0fb,
    0x000a125e,
    0x000ef40d,
    0x000ef437,
    0x000ef3e2,
};
