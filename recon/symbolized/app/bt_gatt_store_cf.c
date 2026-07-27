#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a8bc @ 0x0005a8bc
 * public-name: bt_gatt_store_cf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store_cf                     <= FUN_00053034 @ 0x00053034
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   bt_gatt_store_cf                         <= FUN_0005a8bc @ 0x0005a8bc
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f497c                             @ 0x000f497c
 */
/* Reconstructed FUN_0005a8bc @ 0x5a8bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned long long find_cf_cfg_by_addr(unsigned long, unsigned long);
extern int read_struct_first_word(int);
extern int bt_settings_store_cf(unsigned int,unsigned int,void*,unsigned int);
extern void log_msg_create_3arg(unsigned int,unsigned int,void*);
void bt_gatt_store_cf(unsigned int param_1,unsigned int param_2){
  unsigned long long uVar4; int iVar1; unsigned char* puVar2; unsigned int uVar3;
  unsigned char local_14; unsigned char local_13; int iStack_20;
  struct{unsigned int a,b; int c;} s;
  uVar4=find_cf_cfg_by_addr(param_1, param_2); iVar1=(int)uVar4;
  if(iVar1==0){ puVar2=0; uVar3=0; }
  else{
    local_14=*(volatile unsigned char*)(iVar1+8);
    local_13=(unsigned char)read_struct_first_word(iVar1+0xc);
    uVar3=2; local_13&=1; puVar2=&local_14;
  }
  iStack_20=bt_settings_store_cf(param_1,param_2,puVar2,uVar3);
  if(iStack_20!=0){ s.b=((unsigned long)&rodata_f497c) /*=0xf497c*/; s.a=3; s.c=iStack_20; log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/,0x1840,&s); }
  (void)local_13;
}
