#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032954 @ 0x01032954
 * public-name: FUN_01032954
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01032954 @ 0x1032954  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB TX FIFO pop @ 0x01032954 (Ghidra-gap leaf, extent 0x2e).  Under
 * BASEPRI 0x40 it decrements the queue count at 0x21004a60+0x28 and advances
 * the read index at +0x24 modulo 8.  NOTE (disassembly): the body touches only
 * r1/r2/r3 -- it PRESERVES r0, and FUN_01032de4 relies on that.
 */
void FUN_01032954(void)
{
    volatile unsigned int *q = (volatile unsigned int *)0x21004a60u;
    unsigned int basepri;
    unsigned int v;

    __asm__ volatile ("mrs %0, basepri" : "=r" (basepri));
    __asm__ volatile ("msr basepri_max, %0" :: "r" (0x40u) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");
    q[0x28u / 4u] = q[0x28u / 4u] - 1u;
    v = q[0x24u / 4u] + 1u;
    if (v >= 8u)
        v = 0u;
    q[0x24u / 4u] = v;
    __asm__ volatile ("msr basepri, %0" :: "r" (basepri) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");
}
