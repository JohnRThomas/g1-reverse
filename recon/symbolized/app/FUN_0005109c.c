#include "g1_app_symbols.h"
/* named: FUN_0005109c */
/* Reconstructed FUN_0005109c @ 0x5109c  (parity: 300/300 trials, PROVEN) */

extern int malloc(int);
extern void assert_post_action(void*, unsigned int);
extern void printk(void*, void*, void*, int);
extern void kmutex_dlist_init(void);

void FUN_0005109c(int *param_1)
{
  int iVar1;
  unsigned int uVar2;

  if (param_1 == 0) {
    printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, (void*)"lock != ((void *)0)" /*=0xf23d4*/, (void*)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x179);
    uVar2 = 0x179;
    assert_post_action((void*)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, uVar2);
  }
  iVar1 = malloc(0x14);
  *param_1 = iVar1;
  if (iVar1 != 0) {
    kmutex_dlist_init();
    return;
  }
  printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, (void*)"*lock != ((void *)0)" /*=0xf23d3*/, (void*)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, 0x181);
  printk((void*)"\trecursive lock allocation failed\n" /*=0xf240f*/, 0,0,0);
  uVar2 = 0x181;
  assert_post_action((void*)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" /*=0xf22d5*/, uVar2);
}

