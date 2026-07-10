/* rodata_0x27cc0: literal/pointer table, 16 x uint32 (8 SRAM ptr, 7 flash ptr, 1 const)
 * app-core VA 0x27cc0, 65 bytes emitted. Reader(s): check_work_mode
 * full table (naddr==span/4)
 */
#include <stdint.h>
const struct { uint32_t w[16]; uint8_t tail[1]; } rodata_0x27cc0 = {
    { 0x20003027, 0x20007554, 0x000a1b00, 0x000a0266, 0x20018d84, 0x20003026, 0x20003028, 0x20018d85, 0x20003029, 0x000a030d, 0x20003025, 0x000a028c, 0x000a02ab, 0x000a02cc, 0x000a032b, 0xe92d2301 },
    { 0xf7 },
};
