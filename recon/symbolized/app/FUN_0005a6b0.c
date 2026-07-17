#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a6b0 @ 0x0005a6b0
 * public-name: FUN_0005a6b0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_addr_le                   <= FUN_00056e74 @ 0x00056e74
 *   bt_att_clear_out_of_sync_sent            <= FUN_00082572 @ 0x00082572
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 *   atomic_and_4                             <= FUN_000826f6 @ 0x000826f6
 *   set_change_aware                         <= FUN_00082bb8 @ 0x00082bb8
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_bt_gatt_db_hash_work                   @ 0x200063a0
 *   g_bt_gatt_flags                          @ 0x20006448
 *   g_bt_gatt_cf_cfg                         @ 0x2000aed4
 */
/* Reconstructed FUN_0005a6b0 @ 0x5a6b0  (parity: 300/300 trials, PROVEN) */

extern int FUN_000531d8(unsigned,unsigned,int,int);
extern int ble_conn_unref(int);
extern int bt_conn_lookup_addr_le(int,void*);
extern int bt_att_clear_out_of_sync_sent(void);
extern int bt_addr_le_eq_0(void*,unsigned);
extern int atomic_and_4(unsigned,unsigned,...);
extern int set_change_aware(void*,int);
void FUN_0005a6b0(unsigned p1,unsigned p2,unsigned p3,unsigned p4){
  unsigned uVar1; int iVar2; unsigned char* puVar3; int iVar4;
  atomic_and_4(((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/, 0xfffffff7, p3, p4, p4);
  FUN_000531d8(((unsigned long)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, 0, 0x148, 0);
  uVar1 = ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/;
  iVar4=0;
  puVar3=(unsigned char*)((unsigned long)&g_bt_gatt_cf_cfg) /*=0x2000aed4*/;
  do{
    iVar2=bt_addr_le_eq_0(puVar3+1, uVar1);
    if(iVar2==0 && (int)((unsigned)(unsigned char)puVar3[8]<<0x1f) < 0){
      iVar2=bt_conn_lookup_addr_le(0, puVar3+1);
      if(iVar2!=0){ bt_att_clear_out_of_sync_sent(); ble_conn_unref(iVar2); }
      atomic_and_4((unsigned)(puVar3+0xc), 0xfffffffd);
      set_change_aware(puVar3, 0);
    }
    iVar4=iVar4+1;
    puVar3=puVar3+0x10;
  } while(iVar4!=3);
  return;
}
