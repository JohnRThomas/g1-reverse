#include "g1_app_symbols.h"
/* named: discovery_completed_cb_gatt */
/* Reconstructed discovery_completed_cb_gatt @ 0x189a0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int,...);
extern unsigned bt_gatt_dm_conn_get(void);
extern unsigned bt_gatt_dm_attr_cnt(unsigned);
extern int gatt_service_changed_c_discovery_completed(unsigned,unsigned);
extern int FUN_0004f418(unsigned,unsigned);
extern int bt_gatt_dm_data_release(unsigned);
extern void gatt_discover(unsigned,int);
void discovery_completed_cb_gatt(unsigned param_1, unsigned param_2){
  unsigned uVar1, uVar2; int iVar3; unsigned fmt;
  uVar1 = bt_gatt_dm_conn_get();
  uVar2 = bt_gatt_dm_attr_cnt(param_1);
  if(uVar2 < 2){ DEBUG_PRINT("GATT Service could not be found during the discovery\n" /*=0x9a8c3*/); }
  else {
    DEBUG_PRINT("The discovery procedure for GATT Service succeeded\n" /*=0x9a820*/);
    iVar3 = gatt_service_changed_c_discovery_completed(param_1,param_2);
    fmt = "Could not init GATT Service client object, error: %d\n" /*=0x9a854*/;
    if(iVar3!=0 || (iVar3=FUN_0004f418(param_2,((uintptr_t)&tbl_18a04) /*=0x18a39*/), fmt="Cannot subscribe to Service Changed indication (err %d)\n" /*=0x9a88a*/, iVar3!=0)){
      DEBUG_PRINT(fmt,iVar3);
    }
  }
  iVar3 = bt_gatt_dm_data_release(param_1);
  if(iVar3!=0){ DEBUG_PRINT("Could not release the discovery data, error code: %d\n" /*=0x9a7bc*/,iVar3); }
  gatt_discover(uVar1,0);
  return;
}

