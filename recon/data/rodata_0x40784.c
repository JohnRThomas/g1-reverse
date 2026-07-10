/* rodata_0x40784: const pointer table, 4 x uint32 (4 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x40784, 16 bytes. Reader(s): FUN_00040708
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x40784[4] = {
    0x200034f5,
    0x2001cdd2,
    0x2001cdd1,
    0x2001cdd3,
};
