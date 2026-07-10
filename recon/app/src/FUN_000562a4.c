/* Reconstructed FUN_000562a4 @ 0x562a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072e50(int,int);
extern int FUN_000732d4(int,int);
extern int FUN_00086c78(int,int,int,int,int);
int FUN_000562a4(int param_1, int param_2, int param_3, int param_4){
  int iVar1 = 0;
  volatile int *piVar2;
  while(1){
    if(iVar1==param_2) return 0;
    piVar2 = (volatile int*)(param_1+0xd0);
    if(*piVar2==0) break;
    param_1 += 0xd8;
    iVar1 += 1;
  }
  *piVar2 = 1;
  if(param_1==0) return 0;
  FUN_00086c78(param_1,0,0xd0,(int)piVar2,param_4);
  FUN_000732d4(param_1+0x60, 0x000570a1);
  FUN_00072e50(param_1+0x28, 0x000813d1);
  return param_1;
}

