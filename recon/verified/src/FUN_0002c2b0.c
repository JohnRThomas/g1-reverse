/* Reconstructed FUN_0002c2b0 @ 0x2c2b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00034410(void);
extern int FUN_0003444c(void);
extern int FUN_00019c70(void);
extern int FUN_0002c224(int);
extern int FUN_00034274(void);
extern int FUN_000167a8(void);
extern int FUN_0003443c(int);
extern void DEBUG_PRINT(int,...);
void FUN_0002c2b0(void){
  volatile int *piVar1 = (volatile int*)0x20007554UL;
  while(FUN_00034410()==5 && FUN_0003444c()==2){
    if(*piVar1==0){
      DEBUG_PRINT(0x000a26cbUL);
    } else {
      FUN_00019c70();
    }
    int iVar2 = FUN_0002c224(2);
    if(iVar2 <= 3000){
      FUN_00034274();
      int r = FUN_000167a8();
      if(*(volatile uint8_t*)(r+0xdd)==0){
        FUN_0003443c(0);
        return;
      }
      FUN_0003443c(6);
    }
  }
}

