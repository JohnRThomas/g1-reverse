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
  iVar1 = FUN_00071eac(0x20004c08,0x20028668,0x800,0x00047c49,param_1,0,0,0xfffffff4,0);
  *(volatile int*)0x2000a090UL = iVar1;
  return -(unsigned int)(iVar1 == 0);
}

