/* rodata_0x38600: const pointer table, 8 x uint32 (3 SRAM ptrs, 5 flash ptrs)
 * app-core VA 0x38600, 32 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x38600[8] = {
    0x20007554,
    0x000a95e7,
    0x000a91a4,
    0x000a917d,
    0x000a9195,
    0x000a91c0,
    0x2000a030,
    0x200107e3,
};
