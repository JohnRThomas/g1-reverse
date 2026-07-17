/* readable reconstruction; identity: FUN_000188d8 @ 0x000188d8
 * public-name: discovery_completed_cb_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_completed_cb_ancs              <= FUN_000188d8 @ 0x000188d8
 *   atomic_and                               <= FUN_0007c08e @ 0x0007c08e
 *   bt_gatt_dm_conn_get                      <= FUN_0007f4c8 @ 0x0007f4c8
 *   bt_gatt_dm_data_release                  <= FUN_0007f594 @ 0x0007f594
 * address symbols (name @ address):
 *   ADDR_bt_ancs_data_source_handler_THUMB   @ 0x00018c49
 *   rodata_18ef5                             @ 0x00018ef5
 *   rodata_9a6f2                             @ 0x0009a6f2
 *   rodata_9a71e                             @ 0x0009a71e
 *   rodata_9a74c                             @ 0x0009a74c
 *   rodata_9a788                             @ 0x0009a788
 *   rodata_9a7bc                             @ 0x0009a7bc
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 */
/* Reconstructed FUN_000188d8 @ 0x188d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int log_message(int,...);
extern int gatt_discover(int,...);
extern int FUN_0004ee68(int,...);
extern int FUN_0004f040(int,...);
extern int FUN_0004f0ec(int,...);
extern int atomic_and(int,...);
extern int bt_gatt_dm_conn_get(int callback_object);
extern int bt_gatt_dm_data_release(int,...);
void discovery_completed_cb_ancs(void *param_1, void *param_2){
  int uVar1 = bt_gatt_dm_conn_get((int)param_1);
  log_message(0x9a6f2);
  int iVar2 = FUN_0004ee68((int)param_1,(int)param_2);
  unsigned fmt = 0x9a71e;
  if(iVar2==0){
    *(volatile uint32_t*)0x20006ab4UL |= 2u;
    iVar2 = FUN_0004f040((int)param_2, 0x18ef5);
    if(iVar2!=0) log_message(0x9a74c, iVar2);
    iVar2 = FUN_0004f0ec((int)param_2, 0x18c49);
    fmt = 0x9a788;
    if(iVar2==0) goto L;
  }
  log_message(fmt, iVar2);
L:
  iVar2 = bt_gatt_dm_data_release((int)param_1);
  if(iVar2!=0) log_message(0x9a7bc, iVar2);
  atomic_and(0x20006ab4, 0xfffffffe);
  gatt_discover(uVar1, 1);
}
