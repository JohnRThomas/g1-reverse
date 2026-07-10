#include "g1_app_symbols.h"
/* named: net_buf_frag_last */
/* Reconstructed net_buf_frag_last @ 0x5f304  (parity: 300/300 trials, PROVEN) */

extern int printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d,unsigned int e);
extern int assert_post_action(unsigned int a,unsigned int b);

int net_buf_frag_last(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf" /*=0xf45be*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x236, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x236);
  }
  do {
    iVar1 = param_1;
    param_1 = *(int*)(param_1+4);
  } while (param_1 != 0);
  return iVar1;
}

