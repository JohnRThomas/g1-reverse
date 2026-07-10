#include "g1_net_symbols.h"
/* net-core FUN_01016828 @ 0x1016828  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
__attribute__((naked)) void FUN_01016828(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "movw r1, #0x439\n"
    "movs r0, #0x32\n"
    "push {r3, lr}\n"
    "bl FUN_01008d00\n"
  );
}

