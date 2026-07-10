/* Reconstructed FUN_0004c2d4 @ 0x4c2d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0004c278(uint32_t,uint32_t,uint32_t,int);
extern void FUN_0004d944(uint32_t,int,void*,...);
extern int FUN_0006385c(void);
extern void FUN_00064f30(uint32_t);
extern int FUN_0006540c(void*);
extern void FUN_00065418(uint32_t);

int FUN_0004c2d4(void){
  uint8_t *puVar1;
  int iVar2, iVar4;
  volatile uint32_t local_1c;
  volatile uint32_t local_30; volatile void* local_2c; volatile int iStack_28;
  iVar2 = FUN_0006540c((void*)&local_1c);
  if (iVar2 == 0x0bad0000){
    iVar2 = FUN_0006385c();
    puVar1 = (uint8_t*)0x87bd8UL;
    if (iVar2 < 0){
      FUN_00065418(local_1c & 0xff);
    } else {
      iVar4 = *(int*)(0x87bd8UL+8);
      *(volatile uint8_t*)((volatile char*)&local_1c+1) = (uint8_t)iVar2;
      *(volatile uint16_t*)((volatile char*)&local_1c+2) = 0x807;
      int (*pcVar3)(uint32_t,int,uint32_t,uint32_t);
      pcVar3 = *(void**)(iVar4+4);
      if (pcVar3 != 0){
        iVar2 = pcVar3(0x87bd8, 8, 0x4c419, local_1c);
        if (iVar2 < 0) goto LAB;
        pcVar3 = *(void**)(iVar4+0x10);
        if (pcVar3 != 0){
          iVar2 = pcVar3((uint32_t)(uintptr_t)puVar1, 8, 1, 0);
          if (iVar2 >= 0){
            FUN_00064f30(1u << (local_1c & 0xff));
            FUN_0004c278(local_1c & 0xff, (local_1c>>8)&0xff, (local_1c>>24)&0xff, 1);
            if (iVar2 == 0) return 0;
          }
          goto LAB;
        }
      }
      iVar2 = -0x58;
    }
  } else {
    iVar2 = -0x13;
  }
LAB:
  local_2c = (void*)0xf0a68;
  local_30 = 3;
  iStack_28 = iVar2;
  FUN_0004d944(0x88288, 0x1840, (void*)&local_30, 0);
  return iVar2;
}

