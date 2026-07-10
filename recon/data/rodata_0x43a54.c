/* rodata_0x43a54: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x43a54, 20 bytes. Reader(s): FUN_0004396c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x43a54[5] = {
    0x2000230c,
    0x20007554,
    0x000aacee,
    0x000aa96d,
    0x2000a034,
};
