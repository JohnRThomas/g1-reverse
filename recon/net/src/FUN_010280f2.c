/* net-core FUN_010280f2 @ 0x10280f2  (CFG-directed candidate) */
#include <stdint.h>
#include <stdbool.h>
bool FUN_010280f2(uint32_t bits)
{
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    return (bits & (bits << 1)) == 0u;
}
