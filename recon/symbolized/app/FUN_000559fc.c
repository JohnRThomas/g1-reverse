#include "g1_app_symbols.h"
/* named: FUN_000559fc */
/* Reconstructed FUN_000559fc @ 0x559fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_00081320(uint32_t);
extern void atomic_and_1(uint32_t,uint32_t);
extern int FUN_0008117a(uint32_t);
extern int adv_is_directed(uint32_t);
extern int bt_conn_lookup_state_le(uint32_t,uint32_t,uint32_t);
extern void ble_conn_set_state(void);
extern void ble_conn_unref(int);
extern uint bt_le_adv_set_enable_legacy(uint32_t,int);
uint FUN_000559fc(void){
  int iVar1; uint uVar2; uint32_t uVar3;
  FUN_00081320(((uintptr_t)&g_bt_le_legacy_adv) /*=0x20002018*/);
  atomic_and_1(((uintptr_t)&g_ble_adv_ctx_flags) /*=0x20002028*/,0xffffbfff);
  iVar1=FUN_0008117a(((uintptr_t)&g_ble_adv_ctx_flags) /*=0x20002028*/);
  if(iVar1<<0x18 < 0){
    iVar1=FUN_0008117a(((uintptr_t)&g_ble_adv_ctx_flags) /*=0x20002028*/);
    if(iVar1<<0x15 < 0){
      iVar1=adv_is_directed(((uintptr_t)&g_bt_le_legacy_adv) /*=0x20002018*/);
      if(iVar1==0){ uVar3=4; iVar1=((uintptr_t)&rodata_f2b33) /*=0xf2b33*/; }
      else { uVar3=5; iVar1=((uintptr_t)&g_ble_adv_ctx_peer_addr) /*=0x20002021*/; }
      iVar1=bt_conn_lookup_state_le(*(volatile uint8_t*)((uintptr_t)&g_bt_le_legacy_adv) /*=0x20002018*/,iVar1,uVar3);
      if(iVar1!=0){
        *(volatile uint8_t*)(iVar1+0xc)=0;
        ble_conn_set_state();
        ble_conn_unref(iVar1);
      }
    }
    uVar2=bt_le_adv_set_enable_legacy(((uintptr_t)&g_bt_le_legacy_adv) /*=0x20002018*/,0);
    return uVar2;
  }
  return (uint)(iVar1<<0x18)>>0x1f;
}

