#include "g1_app_symbols.h"
/* named: discovery_completed_cb_ancs */
/* globals referenced:
//   0x20006ab4  g_gatt_discovery_flags       
*/
/* Reconstructed discovery_completed_cb_ancs @ 0x188d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int gatt_discover(int,...);
extern int FUN_0004ee68(int,...);
extern int FUN_0004f040(int,...);
extern int FUN_0004f0ec(int,...);
extern int atomic_and(int,...);
extern int bt_gatt_dm_conn_get(void);
extern int bt_gatt_dm_data_release(int,...);
void discovery_completed_cb_ancs(void *param_1, void *param_2){
  int uVar1 = bt_gatt_dm_conn_get();
  DEBUG_PRINT("The discovery procedure for ANCS succeeded\n" /*=0x9a6f2*/);
  int iVar2 = FUN_0004ee68((int)param_1,(int)param_2);
  unsigned fmt = "Could not init ANCS client object, error: %d\n" /*=0x9a71e*/;
  if(iVar2==0){
    *(volatile uint32_t*)((uintptr_t)&g_gatt_discovery_flags) /*=0x20006ab4*/ |= 2u;
    iVar2 = FUN_0004f040((int)param_2, ((uintptr_t)&tbl_18ed8) /*=0x18ef5*/);
    if(iVar2!=0) DEBUG_PRINT("Failed to enable Notification Source notification (err %d)\n" /*=0x9a74c*/, iVar2);
    iVar2 = FUN_0004f0ec((int)param_2, ((uintptr_t)&tbl_18c30) /*=0x18c49*/);
    fmt = "Failed to enable Data Source notification (err %d)\n" /*=0x9a788*/;
    if(iVar2==0) goto L;
  }
  DEBUG_PRINT(fmt, iVar2);
L:
  iVar2 = bt_gatt_dm_data_release((int)param_1);
  if(iVar2!=0) DEBUG_PRINT("Could not release the discovery data, error code: %d\n" /*=0x9a7bc*/, iVar2);
  atomic_and(((uintptr_t)&g_gatt_discovery_flags) /*=0x20006ab4*/, 0xfffffffe);
  gatt_discover(uVar1, 1);
}

