/* named: __errno_location */
/* Reconstructed __errno_location @ 0x71678  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int __errno_location(void)
{
    return *(volatile int32_t*)0x2000b450UL + 0x78;
}

