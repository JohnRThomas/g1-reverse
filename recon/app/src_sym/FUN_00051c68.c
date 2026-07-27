/* Reconstructed FUN_00051c68 @ 0x51c68  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned long, ...);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_00051c68(void)
{
  unsigned int uVar1;

  uVar1 = 0x000f2561UL;
  printk(0x00099cbdUL,0x000f25c5UL,0x000f2561UL,0x62);
  printk(0x000f25e2UL,0,0,0);
  assert_post_action(uVar1,0x62);
}

