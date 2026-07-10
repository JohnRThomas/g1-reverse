/* Reconstructed FUN_00086f00 @ 0x86f00  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_00051164(void);
extern int FUN_00077c30(int,int,int,int);
extern int FUN_00077c78(int,int,int);
extern int FUN_00079528(int,int);
void FUN_00086f00(int param_1, int param_2, int param_3, int param_4){
  if(param_3 < 0){
    FUN_00077c78(param_1, param_4, 0);
    return;
  }
  int uVar1 = FUN_00077c30(param_1, param_3, param_4, 0);
  if(uVar1 < 0) return;
  if((uint32_t)uVar1 < (uint32_t)param_3) return;
  long long v = FUN_00051164();
  int high = (int)(uint32_t)((unsigned long long)v >> 32);
  int lo = (int)(uint32_t)v;
  int iVar2 = FUN_00079528(lo, *(volatile int16_t*)(high+0xe));
  if(iVar2 >= 0){
    *(volatile uint32_t*)(high+0x54) = *(volatile uint32_t*)(high+0x54) + iVar2;
  } else {
    *(volatile uint16_t*)(high+0xc) = *(volatile uint16_t*)(high+0xc) & ~0x1000;
  }
}

