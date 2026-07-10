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
  DEBUG_PRINT(0x9a6f2);
  int iVar2 = FUN_0004ee68((int)param_1,(int)param_2);
  unsigned fmt = 0x9a71e;
  if(iVar2==0){
    *(volatile uint32_t*)0x20006ab4UL |= 2u;
    iVar2 = FUN_0004f040((int)param_2, 0x18ef5);
    if(iVar2!=0) DEBUG_PRINT(0x9a74c, iVar2);
    iVar2 = FUN_0004f0ec((int)param_2, 0x18c49);
    fmt = 0x9a788;
    if(iVar2==0) goto L;
  }
  DEBUG_PRINT(fmt, iVar2);
L:
  iVar2 = bt_gatt_dm_data_release((int)param_1);
  if(iVar2!=0) DEBUG_PRINT(0x9a7bc, iVar2);
  atomic_and(0x20006ab4, 0xfffffffe);
  gatt_discover(uVar1, 1);
}

