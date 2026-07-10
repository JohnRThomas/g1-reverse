#include "g1_app_symbols.h"
/* named: FUN_0005a6b0 */
/* globals referenced:
//   0x2000aed4  g_bt_gatt_cf_cfg             
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
  atomic_and_4(((uintptr_t)&g_bt_gatt_flags) /*=0x20006448*/, 0xfffffff7, p3, p4, p4);
  FUN_000531d8(((uintptr_t)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, 0, 0x148, 0);
  uVar1 = ((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/;
  iVar4=0;
  puVar3=(unsigned char*)((uintptr_t)&g_bt_gatt_cf_cfg) /*=0x2000aed4*/;
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

