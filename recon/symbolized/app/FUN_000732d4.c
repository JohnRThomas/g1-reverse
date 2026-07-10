#include "g1_app_symbols.h"
/* named: FUN_000732d4 */
/* Reconstructed FUN_000732d4 @ 0x732d4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int);
extern void memset_bytes(int, int, int, unsigned int, unsigned int);

void FUN_000732d4(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;

  if (param_1 == 0) {
    printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,(void*)"dwork != ((void *)0)" /*=0xf82df*/,(void*)"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x340);
    uVar1 = 0x340;
  } else {
    if (param_2 != 0) {
      memset_bytes(param_1,0,0x30,param_4,param_4);
      *(volatile int*)(param_1 + 4) = param_2;
      *(volatile unsigned int*)(param_1 + 0xc) = 0x100;
      return;
    }
    printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,(void*)"handler != ((void *)0)" /*=0xf8230*/,(void*)"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x341);
    uVar1 = 0x341;
  }
  assert_post_action((void*)"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,uVar1);
}

