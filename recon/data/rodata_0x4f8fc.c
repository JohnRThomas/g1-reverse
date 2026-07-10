/* rodata_0x4f8fc: const pointer table, 12 x uint32 (10 flash, 2 const)
 * app-core VA 0x4f8fc, 48 bytes. Reader(s): FUN_0004f860
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f8fc[12] = {
    0x000fa9b4, /* flash */
    0x000f17a1, /* flash */
    0x000f176a, /* flash */
    0x00099cbd, /* flash */
    0x0008ad90, /* flash */
    0x000f17c3, /* flash */
    0x0009a1dd, /* flash */
    0x000f17eb, /* flash */
    0x03010200, /* const */
    0x000f1823, /* flash */
    0x03000005, /* const */
    0x000880f0, /* flash */
};
