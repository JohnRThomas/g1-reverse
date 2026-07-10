/* rodata_0x43964: const pointer table, 2 x uint32 (1 SRAM ptrs, 1 flash ptrs)
 * app-core VA 0x43964, 8 bytes. Reader(s): FUN_000438d0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x43964[2] = {
    0x2000a034,
    0x000aae20,
};
