/* rodata_0x3bde0: const pointer table, 14 x uint32 (5 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x3bde0, 56 bytes. Reader(s): FUN_0003b824
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3bde0[14] = {
    0x000a9831,
    0x000a974b,
    0x2001b817,
    0x20007554,
    0x000a9775,
    0x2000230c,
    0x000a9797,
    0x000a9727,
    0x200024e8,
    0x000a97e4,
    0x000a980b,
    0x000a981a,
    0x000a97bb,
    0x20004978,
};
