/* rodata_0x2f440: literal/pointer table, 8 x uint32 (3 SRAM ptr, 5 flash ptr)
 * app-core VA 0x2f440, 32 bytes emitted. Reader(s): FUN_0002f080
 * literal-pool prefix; Thumb code follows at +0x20 (skipped)
 */
#include <stdint.h>
const uint32_t rodata_0x2f440[8] = {
    0x20007554, /* SRAM */
    0x000a41a0, /* flash */
    0x000a3fbe, /* flash */
    0x20003778, /* SRAM */
    0x20007b7c, /* SRAM */
    0x00088694, /* flash */
    0x000a41b0, /* flash */
    0x000a4162, /* flash */
};
