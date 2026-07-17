/* readable reconstruction; identity: FUN_0005a8bc @ 0x0005a8bc
 * public-name: bt_gatt_store_cf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   bt_gatt_store_cf                         <= FUN_0005a8bc @ 0x0005a8bc
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f497c                             @ 0x000f497c
 */
/* Reconstructed FUN_0005a8bc @ 0x5a8bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned long long find_cf_cfg_by_addr(void);
extern int FUN_0008270c(int);
extern int FUN_00053034(unsigned int,unsigned int,void*,unsigned int);
extern void FUN_00082a42(unsigned int,unsigned int,void*);
void bt_gatt_store_cf(unsigned int param_1,unsigned int param_2){
  unsigned long long uVar4; int iVar1; unsigned char* puVar2; unsigned int uVar3;
  unsigned char local_14; unsigned char local_13; int iStack_20;
  struct{unsigned int a,b; int c;} s;
  uVar4=find_cf_cfg_by_addr(); iVar1=(int)uVar4;
  if(iVar1==0){ puVar2=0; uVar3=0; }
  else{
    local_14=*(volatile unsigned char*)(iVar1+8);
    local_13=(unsigned char)FUN_0008270c(iVar1+0xc);
    uVar3=2; local_13&=1; puVar2=&local_14;
  }
  iStack_20=FUN_00053034(param_1,param_2,puVar2,uVar3);
  if(iStack_20!=0){ s.b=0x000f497c; s.a=3; s.c=iStack_20; FUN_00082a42(0x00088128,0x1840,&s); }
  (void)local_13;
}
