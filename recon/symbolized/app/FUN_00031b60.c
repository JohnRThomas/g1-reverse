#include "g1_app_symbols.h"
/* named: FUN_00031b60 */
/* Reconstructed FUN_00031b60 @ 0x31b60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern int strlen(void*);
extern int FUN_000232b0(void);
extern void memcpy(void*,void*,int);
extern void memset_bytes(void*,int,int);
extern void vdprintf_to_fd(void*,int,int,uint32_t,int);
uint32_t FUN_00031b60(int param_1,uint32_t param_2,uint32_t *param_3,char *param_4){
  uint32_t uVar2=0;
  uint32_t local_38=0;
  uint8_t auStack_34[32];
  memset_bytes(auStack_34,0,0x1c);
  DEBUG_PRINT("join in get_sn_info\n" /*=0xa701c*/);
  if(param_3==0 || param_4==0){
    DEBUG_PRINT("get_sn_info para is NULL\n" /*=0xa7031*/);
    uVar2=0xffffffff;
  } else {
    volatile uint8_t *puVar3=(volatile uint8_t*)(uintptr_t)*param_3;
    puVar3[0]=0x22;
    puVar3[1]=*(volatile uint8_t*)(param_1+1);
    puVar3[2]=3;
    int uVar1=FUN_000232b0();
    vdprintf_to_fd(&local_38,0,0x20,"%s" /*=0xa8c37*/,uVar1);
    uVar1=strlen(&local_38);
    puVar3[3]=(uint8_t)uVar1;
    memcpy((void*)(puVar3+4),&local_38,uVar1);
    *param_4=(char)uVar1+4;
  }
  return uVar2;
}

