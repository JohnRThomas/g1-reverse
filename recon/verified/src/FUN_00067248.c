/* Reconstructed FUN_00067248 @ 0x67248  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern void FUN_000500c8(int);
extern void FUN_00067138(uint32_t);
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa(uint32_t,uint32_t,...);
extern void FUN_000852ba(int, int);

void FUN_00067248(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint uVar3 = *(uint8_t*)((char*)param_1 + 4);
  if (*(volatile char*)(0x2000b384 + uVar3*0x24 + 0x1c) == 0){
    FUN_0007e2fa(0x99cbd, 0xf6e3a, 0xf6df0, 0x255, param_4);
    FUN_0007e2ec(0xf6df0, 0x255);
  }
  FUN_000500c8((*param_1 << 0xc) >> 0x18);
  if (*(volatile int*)(0x2000b384 + uVar3*0x24) != 0){
    *(volatile uint32_t*)(*param_1 + 0x308) = 0x80152;
    FUN_000852ba(*param_1, 0x2000b384 + uVar3*0x24);
  }
  int iVar4 = uVar3*0x24 + 0x2000b384;
  int iVar2 = *param_1;
  uint32_t uVar5 = *(uint32_t*)(iVar2 + 0x50c);
  uint32_t uVar6 = *(uint32_t*)(iVar2 + 0x510);
  if ((int)((uint32_t)*(uint8_t*)(iVar4 + 0x1e) << 0x1f) >= 0){
    FUN_00067138(*(uint32_t*)(iVar2 + 0x508));
    FUN_00067138(uVar6);
    FUN_00067138(uVar5);
    FUN_00067138(*(uint32_t*)(iVar4 + 0x20));
    if ((char)*(uint8_t*)((char*)param_1+4) != 0){
      uVar5 = *(uint32_t*)(*param_1 + 0x514);
      FUN_00067138(*(uint32_t*)(*param_1 + 0x56c));
      FUN_00067138(uVar5);
    }
  }
  *(volatile uint8_t*)(uVar3*0x24 + 0x2000b384 + 0x1c) = 0;
}

