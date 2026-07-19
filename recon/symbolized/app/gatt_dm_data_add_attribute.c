#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e9a0 @ 0x0004e9a0
 * public-name: gatt_dm_data_add_attribute
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_attr_alloc                       <= FUN_0004e8e8 @ 0x0004e8e8
 *   uuid_len_from_type                       <= FUN_0004e98c @ 0x0004e98c
 *   gatt_dm_data_add_attribute               <= FUN_0004e9a0 @ 0x0004e9a0
 *   gatt_dm_log_helper                       <= FUN_0007f406 @ 0x0007f406
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88130                             @ 0x00088130
 *   rodata_f1237                             @ 0x000f1237
 *   rodata_f1253                             @ 0x000f1253
 *   cur_service_val                          @ 0x2000a154
 */
/* Reconstructed FUN_0004e9a0 @ 0x4e9a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int gatt_dm_attr_alloc(int);
extern int uuid_len_from_type(int);
extern void gatt_dm_log_helper(unsigned int,unsigned int,void*);
extern void memcpy(int,unsigned int,int);
int gatt_dm_data_add_attribute(unsigned int* param_1,int param_2){
  int iVar2=((unsigned long)&cur_service_val) /*=0x2000a154*/; int iVar3,iVar4,iVar5,iVar6; short uVar1;
  struct{unsigned int a,b;} s;
  s.b=((unsigned long)&rodata_f1237) /*=0xf1237*/;
  if(*(volatile unsigned int*)(iVar2+0x134)<0x23){
    iVar3=uuid_len_from_type(*(unsigned char*)(*param_1));
    iVar4=gatt_dm_attr_alloc(iVar3+param_2);
    s.b=((unsigned long)&rodata_f1253) /*=0xf1253*/;
    if(iVar4!=0){
      iVar5=*(volatile int*)(iVar2+0x134);
      *(volatile int*)(iVar2+0x134)=iVar5+1;
      iVar5=(iVar5+3)*8; iVar6=iVar2+iVar5;
      *(volatile short*)(iVar6+8)=*(short*)((char*)param_1+0x10);
      uVar1=*(short*)((char*)param_1+0x12);
      *(volatile int*)(iVar6+4)=iVar4+param_2;
      *(volatile char*)(iVar6+10)=(char)uVar1;
      memcpy(iVar4+param_2,*param_1,iVar3);
      return iVar5+4+iVar2;
    }
  }
  s.a=2;
  gatt_dm_log_helper(((unsigned long)&rodata_88130) /*=0x88130*/,0x1040,&s);
  return 0;
}
