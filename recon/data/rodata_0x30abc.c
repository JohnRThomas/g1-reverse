/* rodata_0x30abc: literal/pointer table, 13 x uint32 (1 SRAM ptr, 2 flash ptr, 3 periph reg, 7 const)
 * app-core VA 0x30abc, 52 bytes emitted. Reader(s): FUN_00030754
 * full table (naddr==span/4)
 * NOTE contains nRF5340 peripheral register addresses (0x1000xxxx).
 */
#include <stdint.h>
const uint32_t rodata_0x30abc[13] = {
    0x3c00f091, /* const */
    0x000a49ed, /* flash */
    0x20019dad, /* SRAM */
    0x22202220, /* const */
    0x20222022, /* const */
    0x10002000, /* periph */
    0x10003f80, /* periph */
    0x10003b00, /* periph */
    0x003b0010, /* const */
    0x000a64ed, /* flash */
    0x3c00ffff, /* const */
    0x3c00f011, /* const */
    0xf00a29ed, /* const */
};
