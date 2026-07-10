/* rodata_0x32c00: literal/pointer table, 3 x uint32 (1 SRAM ptr, 2 flash ptr)
 * app-core VA 0x32c00, 12 bytes emitted. Reader(s): FUN_00032b24
 * literal-pool prefix; Thumb code follows at +0xc (skipped)
 */
#include <stdint.h>
const uint32_t rodata_0x32c00[3] = {
    0x000a74b9, /* flash */
    0x0008a208, /* flash */
    0x20019ef5, /* SRAM */
};
