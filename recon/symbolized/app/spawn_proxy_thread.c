#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047ad0 @ 0x00047ad0
 * public-name: spawn_proxy_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_proxy_thread                       <= FUN_00047ad0 @ 0x00047ad0
 * address symbols (name @ address):
 *   ADDR_proxy_thread_handler_THUMB          @ 0x00047c49
 *   g_proxy_thread                           @ 0x20004c08
 *   g_proxy_thread_id                        @ 0x2000a090
 *   g_proxy_thread_stack                     @ 0x20028668
 */
/* Reconstructed FUN_00047ad0 @ 0x47ad0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00071eac(int a,int b,int c,int d,int e,int f,int g,int h,int i);
int spawn_proxy_thread(int param_1)
{
  int iVar1;
  iVar1 = FUN_00071eac(((unsigned long)&g_proxy_thread) /*=0x20004c08*/,((unsigned long)&g_proxy_thread_stack) /*=0x20028668*/,0x800,ADDR_proxy_thread_handler_THUMB /*=0x47c49*/,param_1,0,0,0xfffffff4,0);
  *(volatile int*)((unsigned long)&g_proxy_thread_id) /*=0x2000a090*/ = iVar1;
  return -(unsigned int)(iVar1 == 0);
}
