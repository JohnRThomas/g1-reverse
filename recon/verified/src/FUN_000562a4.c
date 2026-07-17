/* Reconstructed FUN_000562a4 @ 0x562a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072e50(int,int);
extern int FUN_000732d4(int,int);
extern void FUN_00086c78(void *,int,unsigned);
int FUN_000562a4(int param_1, int param_2, int param_3, int param_4){
  int iVar1 = 0;
  volatile int *piVar2;
  while(1){
    if(iVar1==param_2) return 0;
    piVar2 = (volatile int*)(param_1+0xd0);
    int expected = 0;
    if (__atomic_compare_exchange_n(piVar2, &expected, 1, 0,
                                    __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
      break;
    param_1 += 0xd8;
    iVar1 += 1;
  }
  if(param_1==0) return 0;
  FUN_00086c78((void *)param_1,0,0xd0);
  FUN_000732d4(param_1+0x60, 0x000570a1);
  FUN_00072e50(param_1+0x28, 0x000813d1);
  return param_1;
}
