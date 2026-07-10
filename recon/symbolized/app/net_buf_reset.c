#include "g1_app_symbols.h"
/* named: net_buf_reset */
/* Reconstructed net_buf_reset @ 0x5ee6c  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int assert_post_action(unsigned int, unsigned int);

void net_buf_reset(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  int fakeParam1;
  if (*(char *)(param_1 + 9) == 0) {
    if (*(int *)(param_1 + 4) == 0) {
      *(unsigned short *)(param_1 + 0x10) = 0;
      *(unsigned int *)(param_1 + 0xc) = *(unsigned int *)(param_1 + 0x14);
      return;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf->frags == ((void *)0)" /*=0xf53cf*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x5b, param_4);
    uVar1 = 0x5b;
  } else {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf->flags == 0U" /*=0xf53be*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x5a, param_4);
    uVar1 = 0x5a;
  }
  fakeParam1 = assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, uVar1);
  while (1) {
    if (*(int *)(fakeParam1 + 4) == 0) {
      *(unsigned short *)(fakeParam1 + 0x10) = 0;
      *(unsigned int *)(fakeParam1 + 0xc) = *(unsigned int *)(fakeParam1 + 0x14);
      return;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf->frags == ((void *)0)" /*=0xf53cf*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x5b, param_4);
    fakeParam1 = assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x5b);
  }
}

