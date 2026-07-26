/* readable reconstruction; identity: FUN_000189a0 @ 0x000189a0
 * public-name: discovery_completed_cb_gatt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_completed_cb_gatt              <= FUN_000189a0 @ 0x000189a0
 *   gatt_subscribe_service_changed           <= FUN_0004f418 @ 0x0004f418
 *   bt_gatt_dm_conn_get                      <= FUN_0007f4c8 @ 0x0007f4c8
 *   bt_gatt_dm_attr_cnt                      <= FUN_0007f4cc @ 0x0007f4cc
 *   bt_gatt_dm_data_release                  <= FUN_0007f594 @ 0x0007f594
 *   gatt_service_changed_c_discovery_completed <= FUN_0007f8dc @ 0x0007f8dc
 * address symbols (name @ address):
 *   ADDR_indicate_sc_cb_THUMB                @ 0x00018a39
 *   rodata_9a7bc                             @ 0x0009a7bc   [INLINED -- G6 literal batch]
 *   rodata_9a820                             @ 0x0009a820   [INLINED -- G6 literal batch]
 *   rodata_9a854                             @ 0x0009a854
 *   rodata_9a88a                             @ 0x0009a88a
 *   rodata_9a8c3                             @ 0x0009a8c3   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_000189a0 @ 0x189a0  (parity: 300/300 trials, PROVEN) */

extern unsigned bt_gatt_dm_conn_get(unsigned callback_object);
extern unsigned bt_gatt_dm_attr_cnt(unsigned);
extern int gatt_service_changed_c_discovery_completed(unsigned,unsigned);
extern int gatt_subscribe_service_changed(unsigned,unsigned);
extern int bt_gatt_dm_data_release(unsigned);
extern void gatt_discover(unsigned,int);
void discovery_completed_cb_gatt(unsigned param_1, unsigned param_2){
  unsigned uVar1, uVar2; int iVar3; unsigned fmt;
  uVar1 = bt_gatt_dm_conn_get(param_1);
  uVar2 = bt_gatt_dm_attr_cnt(param_1);
  if(uVar2 < 2){ log_message(((unsigned long)"GATT Service could not be found during the discovery\n")); }
  else {
    log_message(((unsigned long)"The discovery procedure for GATT Service succeeded\n"));
    iVar3 = gatt_service_changed_c_discovery_completed(param_1,param_2);
    fmt = 0x9a854;
    if(iVar3!=0 || (iVar3=gatt_subscribe_service_changed(param_2,0x18a39), fmt=0x9a88a, iVar3!=0)){
      log_message(fmt,iVar3);
    }
  }
  iVar3 = bt_gatt_dm_data_release(param_1);
  if(iVar3!=0){ log_message(((unsigned long)"Could not release the discovery data, error code: %d\n"),iVar3); }
  gatt_discover(uVar1,0);
  return;
}
