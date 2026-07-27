#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005ac30 @ 0x0005ac30
 * public-name: gatt_db_hash_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   bt_gatt_store_hash                       <= FUN_0005a250 @ 0x0005a250
 *   gatt_cf_store_all                        <= FUN_0005a91c @ 0x0005a91c
 *   gatt_db_hash_gen                         <= FUN_0005aba8 @ 0x0005aba8
 *   gatt_db_hash_process                     <= FUN_0005ac30 @ 0x0005ac30
 *   k_work_cancel_delayable_sync             <= FUN_000735cc @ 0x000735cc
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 * address symbols (name @ address):
 *   g_bt_gatt_db_hash                        @ 0x20006380
 *   g_bt_gatt_db_hash_work_63d0              @ 0x200063d0
 *   g_bt_gatt_flags                          @ 0x20006448
 */
/* Reconstructed FUN_0005ac30 @ 0x5ac30  (parity: 300/300 trials, PROVEN) */

extern unsigned char* find_cf_cfg(int);
extern void bt_gatt_store_hash(void);
extern void gatt_cf_store_all(void);
extern void gatt_db_hash_gen(void);
extern int k_work_cancel_delayable_sync(int);
extern int atomic_or_0(volatile long*, long);
extern int read_struct_first_word(unsigned long);
extern int bt_gatt_attr_read(unsigned,unsigned,unsigned,unsigned);
void gatt_db_hash_process(unsigned p1,unsigned p2,unsigned p3,unsigned p4,unsigned short p5){
  int iVar1,iVar2;
  k_work_cancel_delayable_sync(((unsigned long)&g_bt_gatt_db_hash_work_63d0) /*=0x200063d0*/ - 0x30);
  iVar1 = read_struct_first_word(((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/);
  if((iVar1<<0x1c) >= 0){ gatt_db_hash_gen(); gatt_cf_store_all(); bt_gatt_store_hash(); }
  iVar1 = find_cf_cfg(p1);
  if(iVar1!=0){
    if((int)((unsigned)*(unsigned char*)(iVar1+8)<<0x1f) < 0){
      iVar2 = read_struct_first_word(iVar1+0xc);
      if((iVar2<<0x1f) >= 0){ atomic_or_0(iVar1+0xc, 2); }
    }
  }
  bt_gatt_attr_read(p3,p4,p5,((unsigned long)&g_bt_gatt_db_hash) /*=0x20006380*/);
  return;
}
