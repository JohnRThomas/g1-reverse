/* Reconstructed FUN_000432d0 @ 0x432d0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_000432d0(void)
{
    uint32_t *p = (uint32_t *)0x2000a030UL;
    (void)__atomic_fetch_or(p, 2u, __ATOMIC_SEQ_CST);
    return 0;
}
