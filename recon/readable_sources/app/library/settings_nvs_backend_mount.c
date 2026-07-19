#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_20         => struct g1_layout_nvs_mount_scratch__stack_1074          [stack_1074; G1-original]
 * Raw function identity: 0x0004e83c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004e83c @ 0x0004e83c
 * public-name: settings_nvs_backend_mount
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   flash_area_get_sectors                   <= FUN_0004e098 @ 0x0004e098
 *   settings_src_register                    <= FUN_0004e3c0 @ 0x0004e3c0
 *   settings_dst_register                    <= FUN_0004e3dc @ 0x0004e3dc
 *   settings_nvs_backend_mount               <= FUN_0004e83c @ 0x0004e83c
 *   settings_nvs_backend_init                <= FUN_0007f344 @ 0x0007f344
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   g_settings_nvs_backend_list_next         @ 0x200027fc
 *   g_settings_nvs_default_backend           @ 0x2000a114
 */
/* Reconstructed FUN_0004e83c @ 0x4e83c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int flash_area_open(int,void*);
extern int flash_area_get_sectors(int,void*,void*);
extern int settings_src_register(void*);
extern int settings_dst_register(void*);
extern int settings_nvs_backend_init(void*);
int settings_nvs_backend_mount(int param_1,int param_2,int param_3,unsigned int param_4){
  unsigned int args[4];
  int iVar1, iVar3; unsigned int uVar4,uVar5; unsigned int uVar2;
  args[0]=(unsigned int)param_1; args[1]=1; args[2]=(unsigned int)param_3; args[3]=param_4;
  iVar3=flash_area_open(9,args);
  if(iVar3==0){
    iVar3=flash_area_get_sectors(9,args+1,args+2);
    iVar1=((unsigned long)&g_settings_nvs_default_backend) /*=0x2000a114*/;
    if(iVar3==0 || iVar3==-0xc){
      if(args[3]<((unsigned long)&rodata_10000) /*=0x10000*/){
        uVar5=0; uVar4=0;
        do{
          uVar4=uVar4+args[3];
          if(*(unsigned int*)(args[0]+8)<uVar4){ uVar5=uVar5&0xffff; break; }
          uVar5=uVar5+1;
        }while(uVar5!=8);
        *(volatile short*)(((unsigned long)&g_settings_nvs_default_backend) /*=0x2000a114*/+0x14)=(short)args[3];
        *(volatile short*)(iVar1+0x16)=(short)uVar5;
        *(int*)(iVar1+8)=*(int*)(args[0]+4);
        *(int*)(iVar1+0x3c)=*(int*)(args[0]+0xc);
        iVar3=settings_nvs_backend_init((void*)iVar1);
        uVar2=((unsigned long)&g_settings_nvs_backend_list_next) /*=0x200027fc*/;
        if(iVar3==0){
          *(int*)(iVar1+4)=((unsigned long)&g_settings_nvs_backend_list_next) /*=0x200027fc*/;
          settings_src_register((void*)iVar1);
          *(int*)(iVar1+4)=uVar2;
          settings_dst_register((void*)iVar1);
        }
      } else { iVar3=-0x21; }
    }
  }
  return iVar3;
}
