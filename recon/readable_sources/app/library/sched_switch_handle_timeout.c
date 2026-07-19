#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073788 @ 0x00073788
 * public-name: sched_switch_handle_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sched_thread_should_preempt              <= FUN_000736ec @ 0x000736ec
 *   sched_switch_handle_timeout              <= FUN_00073788 @ 0x00073788
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   z_abort_timeout                          <= FUN_00074d74 @ 0x00074d74
 * address symbols (name @ address):
 *   rodata_73729                             @ 0x00073729
 *   _kernel                                  @ 0x2000b448
 *   g_sched_ready_runq_nonempty_flag         @ 0x2000b48c
 *   g_percpu_timeout_abort_flag              @ 0x2001d565
 */
/* Reconstructed FUN_00073788 @ 0x73788  (parity: 300/300 trials, PROVEN) */

extern void z_abort_timeout(int a);
extern int sched_thread_should_preempt(int a);
extern void z_add_timeout(int a,int b,int c,int d);
void sched_switch_handle_timeout(int param_1)
{
  unsigned char bVar1;
  int iVar2;
  int iVar3;

  bVar1 = *(volatile unsigned char *)(((unsigned long)&_kernel) /*=0x2000b448*/ + 0x10);
  iVar3 = 0x200069c8 + (unsigned int)bVar1 * 0x18;
  z_abort_timeout(iVar3);
  *(volatile unsigned char *)(((unsigned long)&g_percpu_timeout_abort_flag) /*=0x2001d565*/ + bVar1) = 0;
  iVar2 = sched_thread_should_preempt(param_1);
  if (iVar2 != 0) {
    int t = *(volatile int *)((unsigned long)&g_sched_ready_runq_nonempty_flag) /*=0x2000b48c*/ - 1;
    z_add_timeout(iVar3, ((unsigned long)&rodata_73729) /*=0x73729*/, t, t >> 0x1f);
    return;
  }
}
