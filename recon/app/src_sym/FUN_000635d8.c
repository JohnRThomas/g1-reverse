/* Reconstructed FUN_000635d8 @ 0x635d8  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

unsigned int FUN_000635d8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 > 1) {
    printk(0x00099cbd, 0x000f668a, 0x000f6659, 0xc3, param_4);
    assert_post_action(0x000f6659, 0xc3);
  }
  return *(volatile unsigned int *)(0x50015000UL + (param_1 + 0x150) * 4);
}

