/* Reconstructed FUN_00012c80 @ 0x12c80  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern double FUN_00012db0(void);
extern int FUN_000869dc(double);
extern int FUN_0000de18(double);
extern int FUN_0000dddc(double);
extern int* thunk_FUN_00071678(void);
double FUN_00012c80(int param_1, double dparam){
  double uVar3 = FUN_00012db0();
  if((*(volatile int8_t*)0x200035afUL != -1) && (FUN_000869dc(dparam) != 0)){
    int iVar1 = FUN_0000de18(dparam);
    if(iVar1==0){
      iVar1 = FUN_0000dddc(dparam);
      if(iVar1!=0){ int* puVar2 = thunk_FUN_00071678(); uVar3 = 0.0; *puVar2 = 0x22; }
    } else {
      int* puVar2 = thunk_FUN_00071678(); uVar3 = 0.0; *puVar2 = 0x22;
    }
  }
  return uVar3;
}

