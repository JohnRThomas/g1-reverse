/* rodata_0x447ec: const pointer table, 11 x uint32 (5 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x447ec, 44 bytes. Reader(s): FUN_00044544
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x447ec[11] = {
    0x2000a034,
    0x2001cdd4,
    0x2000230c,
    0x20007554,
    0x000aad8e,
    0x000aab3b,
    0x000aab60,
    0x000aaa58,
    0x200034f6,
    0x000aaa7f,
    0x000aab85,
};
