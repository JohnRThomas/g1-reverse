/* Reconstructed FUN_000432ec @ 0x432ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_000432ec(void)
{
    uint32_t *p = (uint32_t *)0x2000a030UL;
    (void)__atomic_fetch_and(p, 0xfffffffdU, __ATOMIC_SEQ_CST);
    return 0;
}
