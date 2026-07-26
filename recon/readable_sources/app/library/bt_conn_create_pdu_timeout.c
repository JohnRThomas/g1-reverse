#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000569ec @ 0x000569ec
 * public-name: bt_conn_create_pdu_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_create_pdu_timeout               <= FUN_000569ec @ 0x000569ec
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   bt_conn_alloc_pdu_buf                    <= FUN_000836de @ 0x000836de
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3d75                             @ 0x000f3d75   [INLINED -- G6 literal batch]
 *   rodata_f3d84                             @ 0x000f3d84
 *   acl_tx_pool                              @ 0x20003a7c
 */
/* Reconstructed FUN_000569ec @ 0x569ec  (parity: 300/300 trials, PROVEN) */

extern int net_buf_simple_reserve(int,int);
extern void assert_post_action(unsigned,unsigned);
extern int bt_conn_call_4arg_zero(unsigned,unsigned,void*);
extern int bt_conn_alloc_pdu_buf(int,unsigned,unsigned,unsigned);
extern int k_is_in_isr(void);
int bt_conn_create_pdu_timeout(int param_1,int param_2,unsigned param_3,unsigned param_4){
  int iVar1; unsigned local_20, local_1c;
  iVar1 = k_is_in_isr();
  if(iVar1!=0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"!k_is_in_isr()") /*=0xf3d75*/,((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x55f);
    assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x55f);
  }
  if(param_1==0) param_1=((unsigned long)&acl_tx_pool) /*=0x20003a7c*/;
  iVar1=bt_conn_alloc_pdu_buf(param_1,((unsigned long)&acl_tx_pool) /*=0x20003a7c*/,param_3,param_4);
  if(iVar1==0){
    local_1c=((unsigned long)&rodata_f3d84) /*=0xf3d84*/; local_20=2;
    bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/,0x1080,&local_20);
  } else {
    net_buf_simple_reserve(iVar1+0xc, param_2+5);
  }
  return iVar1;
}
