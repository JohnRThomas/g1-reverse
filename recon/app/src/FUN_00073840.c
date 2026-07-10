/* Reconstructed FUN_00073840 @ 0x73840  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_000737d8(int,...);
extern void FUN_0007e2ec(int,...);
extern void FUN_0007e2fa(int,...);
void FUN_00073840(int *param_1){
  if( *(int8_t*)((int)param_1+0xd) < 0
      || (*(uint8_t*)((int)param_1+0xd) & 0x1f)!=0
      || param_1[6]!=0 ) return;
  *(uint8_t*)((int)param_1+0xd) = *(uint8_t*)((int)param_1+0xd) | 0x80;
  int iVar1 = 0x2000b448;
  if(param_1 == (int*)0x20006720){
    FUN_0007e2fa(0x99cbd,0xf84d6,0xf82f4,0xc1);
    FUN_0007e2ec(0xf82f4,0xc1);
  }
  unsigned *puVar2 = (unsigned*)(0x2000b448+0x1c);
  unsigned *puVar3 = 0;
  if((unsigned*)*puVar2 != puVar2) puVar3 = (unsigned*)*puVar2;
  unsigned *puVar4 = *(unsigned**)(0x2000b448+0x20);
  for(; puVar3!=0; puVar3=(unsigned*)*puVar3){
    if( *(int8_t*)((int)param_1+0xe) != *(int8_t*)((int)puVar3+0xe)
        && *(int8_t*)((int)param_1+0xe) < *(int8_t*)((int)puVar3+0xe) ){
      puVar2 = (unsigned*)puVar3[1];
      *param_1 = (int)puVar3;
      param_1[1] = (int)puVar2;
      *puVar2 = (unsigned)param_1;
      puVar3[1] = (unsigned)param_1;
      goto LAB;
    }
    if(puVar3==puVar4) break;
  }
  *param_1 = (int)puVar2;
  param_1[1] = (int)puVar4;
  *puVar4 = (unsigned)param_1;
  *(int**)(iVar1+0x20) = param_1;
LAB:
  FUN_000737d8(0);
}

