/* Reconstructed FUN_0005e6a8 @ 0x5e6a8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005e614(void);
extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned long, ...);
void FUN_0005e6a8(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk(0x00099cbdUL,0x000f52acUL,0x000f5268UL,0x59,param_4);
    assert_post_action(0x000f5268UL,0x59);
  }
  FUN_0005e614();
  return;
}

