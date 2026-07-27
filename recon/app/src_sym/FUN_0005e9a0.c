/* Reconstructed FUN_0005e9a0 @ 0x5e9a0  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned long, ...);

void FUN_0005e9a0(int param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    printk(0x00099cbd, 0x000f5298, 0x000f5268, 0x12a, param_4);
    assert_post_action(0x000f5268, 0x12a);
  }
  *(volatile unsigned short *)(param_1 + 0xe) = param_2 | *(volatile unsigned short *)(param_1 + 0xe);
}

