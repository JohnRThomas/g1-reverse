/* Reconstructed FUN_00064fd4 @ 0x64fd4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00064fd4(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk(0x00099cbdUL,0x000f6a4aUL,0x000f6a09UL,99,param_4);
    assert_post_action(0x000f6a09UL,99);
  }
  *(unsigned int *)(param_2 + 0x80) = 0;
  return;
}

