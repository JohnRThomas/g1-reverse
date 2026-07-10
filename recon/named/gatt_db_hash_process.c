/* named: gatt_db_hash_process */
/* globals referenced:
//   0x20006380  g_bt_gatt_db_hash            
*/
/* Reconstructed gatt_db_hash_process @ 0x5ac30  (parity: 300/300 trials, PROVEN) */

extern int find_cf_cfg(unsigned);
extern int bt_gatt_store_hash(void);
extern int gatt_cf_store_all(void);
extern int gatt_db_hash_gen(void);
extern int FUN_000735cc(int);
extern int atomic_or_0(int,int);
extern int FUN_0008270c(int);
extern int bt_gatt_attr_read.constprop.0(unsigned,unsigned,unsigned,unsigned);
void gatt_db_hash_process(unsigned p1,unsigned p2,unsigned p3,unsigned p4,unsigned short p5){
  int iVar1,iVar2;
  FUN_000735cc(0x200063d0 - 0x30);
  iVar1 = FUN_0008270c(0x20006448);
  if((iVar1<<0x1c) >= 0){ gatt_db_hash_gen(); gatt_cf_store_all(); bt_gatt_store_hash(); }
  iVar1 = find_cf_cfg(p1);
  if(iVar1!=0){
    if((int)((unsigned)*(unsigned char*)(iVar1+8)<<0x1f) < 0){
      iVar2 = FUN_0008270c(iVar1+0xc);
      if((iVar2<<0x1f) >= 0){ atomic_or_0(iVar1+0xc, 2); }
    }
  }
  bt_gatt_attr_read.constprop.0(p3,p4,p5,0x20006380);
  return;
}

