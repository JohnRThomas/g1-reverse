/* net-core FUN_0100f70c @ 0x100f70c  (CFG-directed candidate) */
/* Role: transition count over a signed 32-bit controller word. Back-map: FUN_0100f70c. */
#include <stdint.h>
uint32_t FUN_0100f70c(uint32_t value)
{
    uint32_t folded = value ^ (uint32_t)((int32_t)value >> 1);
    folded = (folded & 0x55555555u) + ((folded >> 1) & 0x55555555u);
    folded = (folded & 0x33333333u) + ((folded >> 2) & 0x33333333u);
    folded = (folded & 0x0f0f0f0fu) + ((folded >> 4) & 0x0f0f0f0fu);
    folded = (folded & 0x00ff00ffu) + ((folded >> 8) & 0x00ff00ffu);
    return (folded + (folded >> 16)) & 0xffu;
}
