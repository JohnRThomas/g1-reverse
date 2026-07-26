#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0204                    [param_0204; library]
 * Raw function identity: 0x00056080.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00056080 @ 0x00056080
 * public-name: net_buf_destroy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy                          <= FUN_00056080 @ 0x00056080
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3aa8                             @ 0x000f3aa8
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 */
/* Reconstructed FUN_00056080 @ 0x56080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef int (*fnptr_t)(int,int,int);
extern unsigned long long assert_post_action(int a,int b);
extern void net_pkt_skip(int a);
void net_buf_destroy(int param_1, int param_2)
{
  fnptr_t UNRECOVERED_JUMPTABLE;
  int uVar1;
  if (param_2 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f3aa8) /*=0xf3aa8*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x46);
    param_2 = (int)(assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x46) >> 32);
  }
  UNRECOVERED_JUMPTABLE = (fnptr_t)*(volatile uint32_t *)(param_2 + 4);
  uVar1 = *(volatile int *)(param_2 + 8);
  *(volatile int *)(param_2 + 0xc) = 0;
  *(volatile int *)(param_2 + 4) = 0;
  *(volatile int *)(param_2 + 8) = 0;
  net_pkt_skip(((unsigned long)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/);
  (*UNRECOVERED_JUMPTABLE)(param_1, uVar1, 0xffffff92);
}
