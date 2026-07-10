/* rodata_0x438c8: const pointer table, 2 x uint32 (1 SRAM ptrs, 1 flash ptrs)
 * app-core VA 0x438c8, 8 bytes. Reader(s): FUN_0004382c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x438c8[2] = {
    0x2000a034,
    0x000aae20,
};
