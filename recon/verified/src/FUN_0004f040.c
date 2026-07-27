/* Reconstructed FUN_0004f040 @ 0x4f040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007f612(void*, int);
extern int FUN_0005c3c4(int, int *);
extern void FUN_0007f5d8(volatile int *, int);
extern void FUN_0004d944(uint32_t, int, void*, int);

int FUN_0004f040(volatile uint32_t *param_1, int param_2){
  int iVar1;
  volatile uint32_t local_28, local_24, iStack_20;
  if (param_1 == 0 || param_2 == 0){
    iVar1 = -0x16;
  } else {
    iVar1 = FUN_0007f612((void*)(param_1 + 1), 0);
    if (iVar1 == 0){
      param_1[0x20a] = 0x7f635;
      *(volatile uint16_t*)(param_1 + 0x20e) = 1;
      *(volatile uint16_t*)(param_1 + 0x20d) = *(volatile uint16_t*)((char*)param_1 + 10);
      *(volatile uint16_t*)((char*)param_1 + 0x836) = *(volatile uint16_t*)(param_1 + 3);
      param_1[0x20f] |= 1;
      param_1[0x211] = param_2;
      iVar1 = FUN_0005c3c4(param_1[0], (void*)(param_1 + 0x20a));
      if (iVar1 != 0){
        FUN_0007f5d8((void*)(param_1 + 1), 0);
        local_24 = 0xf159e;
        local_28 = 3;
        iStack_20 = iVar1;
        FUN_0004d944(0x880e8, 0x1840, (void*)&local_28, 0);
      }
    } else {
      iVar1 = -0x78;
    }
  }
  return iVar1;
}

