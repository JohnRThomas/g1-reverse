/* readable reconstruction; identity: FUN_000559fc @ 0x000559fc
 * public-name: legacy_adv_stop_cleanup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adv_is_directed                          <= FUN_00055698 @ 0x00055698
 *   legacy_adv_stop_cleanup                  <= FUN_000559fc @ 0x000559fc
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_set_state                       <= FUN_00056704 @ 0x00056704
 *   bt_conn_lookup_state_le                  <= FUN_00056f08 @ 0x00056f08
 *   deref_conn_field0                        <= FUN_0008117a @ 0x0008117a
 *   atomic_and_1                             <= FUN_00081180 @ 0x00081180
 *   bt_le_adv_set_enable_legacy              <= FUN_000812d2 @ 0x000812d2
 *   cancel_delayable_work_field18            <= FUN_00081320 @ 0x00081320
 * address symbols (name @ address):
 *   rodata_f2b33                             @ 0x000f2b33
 *   g_bt_le_legacy_adv                       @ 0x20002018
 *   g_ble_adv_ctx_peer_addr                  @ 0x20002021
 *   g_ble_adv_ctx_flags                      @ 0x20002028
 */
/* Reconstructed FUN_000559fc @ 0x559fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void cancel_delayable_work_field18(uint32_t);
extern void atomic_and_1(uint32_t,uint32_t);
extern int deref_conn_field0(uint32_t);
extern int adv_is_directed(uint32_t);
extern int bt_conn_lookup_state_le(uint32_t,uint32_t,uint32_t);
extern void ble_conn_set_state(void);
extern void ble_conn_unref(int);
extern uint bt_le_adv_set_enable_legacy(uint32_t,int);
uint legacy_adv_stop_cleanup(void){
  int iVar1; uint uVar2; uint32_t uVar3;
  cancel_delayable_work_field18(0x20002018);
  atomic_and_1(0x20002028,0xffffbfff);
  iVar1=deref_conn_field0(0x20002028);
  if(iVar1<<0x18 < 0){
    iVar1=deref_conn_field0(0x20002028);
    if(iVar1<<0x15 < 0){
      iVar1=adv_is_directed(0x20002018);
      if(iVar1==0){ uVar3=4; iVar1=0xf2b33; }
      else { uVar3=5; iVar1=0x20002021; }
      iVar1=bt_conn_lookup_state_le(*(volatile uint8_t*)0x20002018UL,iVar1,uVar3);
      if(iVar1!=0){
        *(volatile uint8_t*)(iVar1+0xc)=0;
        ble_conn_set_state();
        ble_conn_unref(iVar1);
      }
    }
    uVar2=bt_le_adv_set_enable_legacy(0x20002018,0);
    return uVar2;
  }
  return (uint)(iVar1<<0x18)>>0x1f;
}
