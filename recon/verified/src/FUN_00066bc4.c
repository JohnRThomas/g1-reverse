/* Reconstructed FUN_00066bc4 @ 0x66bc4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0006649c(void);
extern int FUN_000664f0(int);
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,int,uint32_t);

int FUN_00066bc4(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint8_t r4 = *(volatile uint8_t*)0x2000b378UL;
  if (r4 == 0){
    FUN_0007e2fa(0x99cbd, 0xf6d9a, 0xf6d5e, 0x2e8, param_4);
    FUN_0007e2ec(0xf6d5e, 0x2e8);
  }
  int iVar3 = 0x0bad000a;
  if ((param_2 & 3) == 0){
    if (*(volatile int*)0x2000b348UL == 0){
      *(volatile uint32_t*)(0x5002b000UL+0x51c) = param_2;
      *(volatile uint32_t*)(0x5002b000UL+0x520) = param_1;
      *(volatile uint8_t*)(0x2000b348UL+0x39) = 0;
      if (*(volatile uint8_t*)0x2000b380UL != 0 ||
          (iVar3 = FUN_000664f0(1), iVar3 != 0x0bad0007)){
        *(volatile uint32_t*)(0x5002b000UL+0x100) = 0;
        *(volatile uint32_t*)(0x5002b000UL+0xc) = 1;
        return FUN_0006649c();
      }
    } else {
      iVar3 = 0x0bad000b;
      if (r4 == 1){
        *(volatile uint32_t*)(0x5002b000UL+0x51c) = param_2;
        *(volatile uint32_t*)(0x5002b000UL+0x520) = param_1;
        *(volatile uint8_t*)(0x2000b348UL+0x39) = 0;
        *(volatile uint8_t*)(0x2000b348UL+0x30) = 4;
        *(volatile uint32_t*)(0x5002b000UL+0x100) = 0;
        *(volatile uint32_t*)(0x5002b000UL+0x304) = 1;
        if (*(volatile uint8_t*)0x2000b380UL == 0){
          FUN_000664f0(0);
          iVar3 = 0x0bad0000;
        } else {
          *(volatile uint32_t*)(0x5002b000UL+0xc) = 1;
          iVar3 = 0x0bad0000;
        }
      }
    }
  }
  return iVar3;
}

