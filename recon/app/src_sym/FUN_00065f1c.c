/* Reconstructed FUN_00065f1c @ 0x65f1c  (parity: 300/300 trials, PROVEN) */

extern void nvmc_readonly_mode_set(void);
extern void printk(unsigned long, ...);
extern void assert_post_action(unsigned int a, unsigned int b);

unsigned int FUN_00065f1c(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if ((unsigned int)param_1 >= 0x100000u) {
    printk(0x99cbd, 0xf6c8e, 0xf6c32, 0x107, param_4);
    assert_post_action(0xf6c32, 0x107);
    return 0x0bad000a;
  }
  if (((unsigned int)param_1 & 0xfff) != 0) {
    return 0x0bad000a;
  }
  *(volatile unsigned int *)(0x50039000UL + 0x584) = 2;
  *(volatile unsigned int *)(0x50039000UL + 0x504) = 2;
  *param_1 = 0xffffffff;
  while (((int)(*(volatile unsigned int *)(0x50039000UL + 0x400) << 0x1f)) >= 0) {}
  nvmc_readonly_mode_set();
  return 0x0bad0000;
}

