/* named: settings_nvs_backend_mount */
/* Reconstructed settings_nvs_backend_mount @ 0x4e83c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int flash_area_open(int,void*);
extern int flash_area_get_sectors(int,void*,void*);
extern int sys_slist_append(void*);
extern int settings_backend_ptr_store(void*);
extern int settings_nvs_backend_init(void*);
int settings_nvs_backend_mount(int param_1,int param_2,int param_3,unsigned int param_4){
  int local_20[3]; unsigned int local_14;
  int iVar1, iVar3; unsigned int uVar4,uVar5; unsigned int uVar2;
  local_20[1]=1; local_20[0]=param_1; local_20[2]=param_3; local_14=param_4;
  iVar3=flash_area_open(9,local_20);
  if(iVar3==0){
    iVar3=flash_area_get_sectors(9,local_20+1,local_20+2);
    iVar1=*(volatile int*)0x2000a114UL;
    if(iVar3==0 || iVar3==-0xc){
      if(local_14<0x10000){
        uVar5=0; uVar4=0;
        do{
          uVar4=uVar4+local_14;
          if(*(unsigned int*)(local_20[0]+8)<uVar4){ uVar5=uVar5&0xffff; break; }
          uVar5=uVar5+1;
        }while(uVar5!=8);
        *(volatile short*)(0x2000a114UL+0x14)=(short)local_14;
        *(short*)(iVar1+0x16)=(short)uVar5;
        *(int*)(iVar1+8)=*(int*)(local_20[0]+4);
        *(int*)(iVar1+0x3c)=*(int*)(local_20[0]+0xc);
        iVar3=settings_nvs_backend_init((void*)iVar1);
        uVar2=*(volatile unsigned int*)0x200027fcUL;
        if(iVar3==0){
          *(int*)(iVar1+4)=*(volatile unsigned int*)0x200027fcUL;
          sys_slist_append((void*)iVar1);
          *(int*)(iVar1+4)=uVar2;
          settings_backend_ptr_store((void*)iVar1);
        }
      } else { iVar3=-0x21; }
    }
  }
  return iVar3;
}

