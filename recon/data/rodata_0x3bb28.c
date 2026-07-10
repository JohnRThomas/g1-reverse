/* rodata_0x3bb28: const pointer table, 16 x uint32 (3 SRAM ptrs, 13 flash ptrs)
 * app-core VA 0x3bb28, 64 bytes. Reader(s): FUN_0003b824
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3bb28[16] = {
    0x20004978,
    0x2000230c,
    0x20007554,
    0x000a9831,
    0x000a960d,
    0x000a9629,
    0x000a9654,
    0x000a9679,
    0x000a9690,
    0x000aae20,
    0x000a96ac,
    0x000a96c8,
    0x000a96e0,
    0x000a9709,
    0x000a9727,
    0x000a8c57,
};
