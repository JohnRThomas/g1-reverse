/* rodata_0x3b584: const pointer table, 16 x uint32 (6 SRAM ptrs, 10 flash ptrs)
 * app-core VA 0x3b584, 64 bytes. Reader(s): FUN_0003af78
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3b584[16] = {
    0x20007554,
    0x000a957d,
    0x000a93a8,
    0x000a0fe5,
    0x000aae20,
    0x20007570,
    0x2000230c,
    0x2000756c,
    0x0009f929,
    0x000a93da,
    0x000a9437,
    0x000a926f,
    0x20004950,
    0x20007aa0,
    0x000a9465,
    0x000a8c57,
};
