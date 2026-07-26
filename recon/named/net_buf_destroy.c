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
typedef int (*fnptr_t)(int,int,int);
extern void printk(int a,int b,int c,int d);
extern unsigned long long assert_post_action(int a,int b);
extern void net_pkt_skip(int a);
void net_buf_destroy(int param_1, int param_2)
{
  fnptr_t UNRECOVERED_JUMPTABLE;
  int uVar1;
  if (param_2 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0xf3aa8, 0xf3a5d, 0x46);
    param_2 = (int)(assert_post_action(0xf3a5d, 0x46) >> 32);
  }
  UNRECOVERED_JUMPTABLE = (fnptr_t)*(volatile uint32_t *)(param_2 + 4);
  uVar1 = *(volatile int *)(param_2 + 8);
  *(volatile int *)(param_2 + 0xc) = 0;
  *(volatile int *)(param_2 + 4) = 0;
  *(volatile int *)(param_2 + 8) = 0;
  net_pkt_skip(0x20003a60);
  (*UNRECOVERED_JUMPTABLE)(param_1, uVar1, 0xffffff92);
}
