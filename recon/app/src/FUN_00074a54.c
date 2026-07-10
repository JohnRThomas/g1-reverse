/* Reconstructed FUN_00074a54 @ 0x74a54  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern void FUN_00073840(void*);
extern void FUN_00074274(void*);
extern void FUN_00074d74(void*);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(uint32_t, uint32_t, ...);

int FUN_00074a54(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb;
  int iVar3, iVar4;
  int *piVar5;
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = FUN_00072040(0x2000b490);
  if (iVar3 == 0){
    FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72, param_4);
    FUN_0007e2fa(0xf0935, 0x2000b490);
    FUN_0007e2ec(0xf08c7, 0x72);
  } else {
    FUN_00072078(0x2000b490);
    piVar5 = (int*)*param_1;
    if (param_1 == piVar5) iVar3 = 0;
    else if (piVar5 == 0) iVar3 = 0;
    else {
      piVar5[0x24] = param_2;
      piVar5[5] = param_3;
      FUN_00074274(piVar5);
      FUN_00074d74(piVar5 + 6);
      FUN_00073840(piVar5);
    }
    iVar4 = FUN_0007205c(0x2000b490);
    if (iVar4 != 0){
      __asm volatile("msr basepri, %0" :: "r"(sb));
      __asm volatile("isb sy");
      return iVar3;
    }
    FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0xf0, param_4);
    FUN_0007e2fa(0xf090b, 0x2000b490);
    FUN_0007e2ec(0xf08c7, 0xf0);
  }
  return iVar3;
}

