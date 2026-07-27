/* Reconstructed FUN_00031bd8 @ 0x31bd8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
unsigned FUN_00031bd8(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4){
  int iVar1; uint16_t uVar2; uint8_t *puVar3;
  DEBUG_PRINT(0xa704b);
  if(param_3==0 || param_4==0){ DEBUG_PRINT(0xa6603); return 0xffffffff; }
  puVar3=(uint8_t*)*param_3;
  *puVar3=5; puVar3[1]=1; puVar3[2]=3; puVar3[3]=6;
  if(*(char*)(param_1+2)==1){ iVar1=FUN_000167a8(); *(uint32_t*)(puVar3+4)=*(uint32_t*)(iVar1+0xfda); uVar2=*(uint16_t*)(iVar1+0xfde); }
  else { if(*(char*)(param_1+2)!=0) goto LAB; iVar1=FUN_000167a8(); *(uint32_t*)(puVar3+4)=*(uint32_t*)(iVar1+0xfe0); uVar2=*(uint16_t*)(iVar1+0xfe4); }
  *(uint16_t*)(puVar3+8)=uVar2;
  LAB: *param_4=10; return 0;
}

