/* Reconstructed FUN_00031b60 @ 0x31b60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern int FUN_0000ef12(void*);
extern int FUN_000232b0(void);
extern void FUN_00086c04(void*,void*,int);
extern void FUN_00086c78(void*,int,int);
extern void FUN_00086f00(void*,int,int,uint32_t,int);
uint32_t FUN_00031b60(int param_1,uint32_t param_2,uint32_t *param_3,char *param_4){
  uint32_t uVar2=0;
  struct {
    uint32_t payload;
    uint8_t scratch[28];
  } workspace;
  workspace.payload = 0;
  FUN_00086c78(workspace.scratch,0,0x1c);
  DEBUG_PRINT(0xa701c);
  if(param_3==0 || param_4==0){
    DEBUG_PRINT(0xa7031);
    uVar2=0xffffffff;
  } else {
    volatile uint8_t *puVar3=(volatile uint8_t*)(uintptr_t)*param_3;
    puVar3[0]=0x22;
    puVar3[1]=*(volatile uint8_t*)(param_1+1);
    puVar3[2]=3;
    int uVar1=FUN_000232b0();
    FUN_00086f00(&workspace.payload,0,0x20,0xa8c37,uVar1);
    uVar1=FUN_0000ef12(&workspace.payload);
    puVar3[3]=(uint8_t)uVar1;
    FUN_00086c04((void*)(puVar3+4),&workspace.payload,uVar1);
    *param_4=(char)uVar1+4;
  }
  return uVar2;
}
