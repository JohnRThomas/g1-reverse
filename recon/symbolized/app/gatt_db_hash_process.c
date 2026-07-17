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
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 * address symbols (name @ address):
 *   g_bt_gatt_db_hash                        @ 0x20006380
 *   g_bt_gatt_db_hash_work_63d0              @ 0x200063d0
 *   g_bt_gatt_flags                          @ 0x20006448
 */
/* Reconstructed FUN_0005ac30 @ 0x5ac30  (parity: 300/300 trials, PROVEN) */

extern int find_cf_cfg(unsigned);
extern int bt_gatt_store_hash(void);
extern int gatt_cf_store_all(void);
extern int gatt_db_hash_gen(void);
extern int FUN_000735cc(int);
extern int atomic_or_0(int,int);
extern int FUN_0008270c(int);
extern int FUN_00082932(unsigned,unsigned,unsigned,unsigned);
void gatt_db_hash_process(unsigned p1,unsigned p2,unsigned p3,unsigned p4,unsigned short p5){
  int iVar1,iVar2;
  FUN_000735cc(((unsigned long)&g_bt_gatt_db_hash_work_63d0) /*=0x200063d0*/ - 0x30);
  iVar1 = FUN_0008270c(((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/);
  if((iVar1<<0x1c) >= 0){ gatt_db_hash_gen(); gatt_cf_store_all(); bt_gatt_store_hash(); }
  iVar1 = find_cf_cfg(p1);
  if(iVar1!=0){
    if((int)((unsigned)*(unsigned char*)(iVar1+8)<<0x1f) < 0){
      iVar2 = FUN_0008270c(iVar1+0xc);
      if((iVar2<<0x1f) >= 0){ atomic_or_0(iVar1+0xc, 2); }
    }
  }
  FUN_00082932(p3,p4,p5,((unsigned long)&g_bt_gatt_db_hash) /*=0x20006380*/);
  return;
}
