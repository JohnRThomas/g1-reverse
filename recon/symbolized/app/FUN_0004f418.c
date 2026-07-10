#include "g1_app_symbols.h"
/* named: FUN_0004f418 */
/* Reconstructed FUN_0004f418 @ 0x4f418  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0005c3c4(uint32_t, void*);
extern void FUN_0004d944(uint32_t, int, void*, int);

int FUN_0004f418(volatile int *param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int iVar1;
  unsigned uVar2;
  volatile unsigned *puVar3;
  volatile uint32_t local_28, local_24, uStack_18;
  volatile int iStack_20;
  if (param_1 == 0 || *param_1 == 0 || param_2 == 0){
    iVar1 = -0x16;
  } else {
    puVar3 = (volatile unsigned*)(param_1 + 10);
    uVar2 = *puVar3;
    *puVar3 = uVar2 | 1;
    iVar1 = ((uintptr_t)&rodata_7f895) /*=0x7f895*/;
    if ((uVar2 & 1) == 0){
      param_1[9] = param_2;
      param_1[2] = iVar1;
      *(volatile int16_t*)(param_1 + 6) = 2;
      param_1[5] = param_1[1];
      param_1[7] |= 1;
      uStack_18 = param_4;
      iVar1 = FUN_0005c3c4((uint32_t)*param_1, (void*)(param_1 + 2));
      if (iVar1 != 0){
        *puVar3 = *puVar3 & 0xfffffffe;
        local_24 = "Subscribe Service Changed failed (err %d)" /*=0xf1625*/;
        local_28 = 3;
        iStack_20 = iVar1;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x881c0*/, 0x1840, (void*)&local_28, 0);
      }
    } else {
      iVar1 = -0x78;
    }
  }
  return iVar1;
}

