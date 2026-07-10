/* net-core FUN_01012c08 @ 0x1012c08  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
__attribute__((naked)) void FUN_01012c08(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "movw r1, #0x35b\n"
    "movs r0, #6\n"
    "push {r3, lr}\n"
    "bl FUN_01008d00\n"
  );
}

