/* Reconstructed FUN_0005e080 @ 0x5e080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00082ff6(int,int);
extern int FUN_0005e9d0(int,int,int,int);
extern uint32_t FUN_00052cdc(int);
extern void FUN_00083074(uint32_t,int,void*);
extern void FUN_00083090(int,uint32_t);
extern void FUN_0005daf0(int);

uint32_t FUN_0005e080(int param_1, int param_2){
  uint8_t bVar1;
  int iVar2, iVar5, iVar6;
  uint32_t uVar3;
  uint16_t *puVar4;
  volatile uint32_t local_28, local_24, uStack_20;
  volatile uint16_t local_1c;
  iVar6 = *(int*)(param_1+0xf0);
  iVar2 = FUN_00082ff6(param_1+4, 0xd);
  if (iVar2 != 0){
    iVar5 = iVar6 + 0x90;
    puVar4 = *(uint16_t**)(param_2+0xc);
    iVar2 = FUN_0005e9d0(4, *(uint8_t*)(iVar6+8), iVar5, param_2);
    if (iVar2 == 0){
      uStack_20 = FUN_00052cdc(iVar5);
      local_24 = 0xf4e60;
      local_1c = 0x200;
      local_28 = 0x1000003;
      FUN_00083074(0x88180, 0x1c40, (void*)&local_28);
      return 8;
    }
    *(uint16_t*)(iVar2+0x18) = *puVar4;
    *(uint32_t*)(iVar2+0x10) = *(uint32_t*)((char*)puVar4+2);
    *(uint32_t*)(iVar2+0x14) = *(uint32_t*)((char*)puVar4+6);
  }
  bVar1 = *(uint8_t*)(param_1+0xe9);
  *(uint8_t*)(param_1+0xe9) = bVar1 & 0xfe;
  if ((int)((uint32_t)bVar1 << 0x1e) < 0){
    uVar3 = 8;
  } else {
    if ((int)((uint32_t)bVar1 << 0x1d) >= 0) goto LAB;
    uVar3 = 10;
  }
  FUN_00083090(param_1, uVar3);
LAB:
  if (*(short*)(param_1+0xe8) == 0){
    FUN_0005daf0(param_1);
  }
  return 0;
}
