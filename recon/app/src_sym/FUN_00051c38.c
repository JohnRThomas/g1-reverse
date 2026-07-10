/* Reconstructed FUN_00051c38 @ 0x51c38  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_00051c38(void)
{
  unsigned int uVar1;

  uVar1 = 0x000f2561UL;
  printk(0x00099cbdUL,0x000f25c5UL,0x000f2561UL,0x71);
  printk(0x000f25e2UL,0,0,0);
  assert_post_action(uVar1,0x71);
}

