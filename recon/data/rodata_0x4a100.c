/* rodata_0x4a100: MD5 per-round constant table (K[]), 27 x uint32
 * app-core VA 0x4a100, 108 bytes. Reader(s): FUN_00049acc
 * K[i] = floor(2^32 * abs(sin(i+1))); first entry 0xd76aa478 confirms MD5. */
#include <stdint.h>
const uint32_t rodata_0x4a100[27] = {
    0xa4beea44,
    0x4bdecfa9,
    0xf6bb4b60,
    0xbebfbc70,
    0x289b7ec6,
    0xeaa127fa,
    0xd4ef3085,
    0x04881d05,
    0xd9d4d039,
    0xe6db99e5,
    0x1fa27cf8,
    0xc4ac5665,
    0xf4292244,
    0x432aff97,
    0xab9423a7,
    0xfc93a039,
    0x655b59c3,
    0x8f0ccc92,
    0x85845dd1,
    0x6fa87e4f,
    0xfe2ce6e0,
    0xa3014314,
    0x4e0811a1,
    0xf7537e82,
    0xbd3af235,
    0x2ad7d2bb,
    0xeb86d391,
};
