/* net-core FUN_0100ebb8 @ 0x100ebb8  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
__attribute__((naked)) void FUN_0100ebb8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "movw r1, #0x2bf\n"
    "movs r0, #0x10\n"
    "push {r3, lr}\n"
    "bl FUN_01008d00\n"
  );
}

