/* rodata_0x49310: const pointer table, 19 x uint32 (6 SRAM ptrs, 13 flash ptrs)
 * app-core VA 0x49310, 76 bytes. Reader(s): FUN_00049090
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x49310[19] = {
    0x2000230c,
    0x20007554,
    0x000f01aa,
    0x000efb2e,
    0x000efb50,
    0x0007d86d,
    0x20004ce0,
    0x2001d447,
    0x20002544,
    0x200038c4,
    0x000efb9f,
    0x000efbb7,
    0x000efbe5,
    0x000efc00,
    0x000efc2d,
    0x000efc62,
    0x000efc92,
    0x000efcaf,
    0x000efb7a,
};
