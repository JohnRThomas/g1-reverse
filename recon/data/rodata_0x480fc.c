/* rodata_0x480fc: magic-tagged descriptor/pointer table
 * app-core VA 0x480fc, 80 bytes. Reader(s): FUN_00047c48
 * word[0] = 0x5aa5aa5a sentinel/magic; remaining 19 words are SRAM/flash pointers. */
#include <stdint.h>
const uint32_t rodata_0x480fc[20] = {
    0x5aa5aa5a, /* magic 0x5aa5aa5a */
    0x2000a08c,
    0x2000a088,
    0x20007554,
    0x000ef76f,
    0x000ef1a8,
    0x2001d34b,
    0x2000a084,
    0x2001d264,
    0x2000a07c,
    0x2001d26e,
    0x000ef0fb,
    0x000ef1ea,
    0x000ef214,
    0x2001d262,
    0x000ef260,
    0x2000a078,
    0x2000a080,
    0x000ef29b,
    0x2001d263,
};
