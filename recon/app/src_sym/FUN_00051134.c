/* Reconstructed FUN_00051134 @ 0x51134  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);
extern void FUN_00072558(void);
void FUN_00051134(int param_1, int param_2, int param_3, int param_4)
{
  if (param_1 == 0) {
    printk(0x00099cbdUL, 0x000f23d4UL, 0x000f22d5UL, 0x1c2, param_4);
    assert_post_action(0x000f22d5UL, 0x1c2);
  }
  FUN_00072558();
}

