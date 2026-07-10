#include "g1_app_symbols.h"
/* named: spawn_proxy_thread */
/* globals referenced:
//   0x2000a090  g_proxy_thread_id            [g_obj_2000a018.f_78]
*/
/* Reconstructed spawn_proxy_thread @ 0x47ad0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00071eac(int a,int b,int c,int d,int e,int f,int g,int h,int i);
int spawn_proxy_thread(int param_1)
{
  int iVar1;
  iVar1 = FUN_00071eac(((uintptr_t)&g_proxy_thread) /*=0x20004c08*/,((uintptr_t)&g_proxy_thread_stack) /*=0x20028668*/,0x800,((uintptr_t)&tbl_47c3c) /*=0x47c49*/,param_1,0,0,0xfffffff4,0);
  *(volatile int*)((uintptr_t)&g_proxy_thread_id) /*=0x2000a090*/ = iVar1;
  return -(unsigned int)(iVar1 == 0);
}

