/* rodata_0x34af4: const pointer table, 16 x uint32 (2 SRAM ptrs, 14 flash ptrs)
 * app-core VA 0x34af4, 64 bytes. Reader(s): FUN_00034980
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x34af4[16] = {
    0x2000230c,
    0x20007554,
    0x000a83e9,
    0x000a838d,
    0x0009d79d,
    0x000a83aa,
    0x0009d759,
    0x0009b257,
    0x0009d76c,
    0x0009d775,
    0x000f3fde,
    0x0009d790,
    0x000a83ca,
    0x000a83d1,
    0x000a81b7,
    0x000a83d8,
};
