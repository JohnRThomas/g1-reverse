/* Reconstructed panel_on @ 0x46dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00015df4(void);
extern int FUN_0001655c(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0002e67c(void);
extern int FUN_00047538(void);
int panel_on(int param_1){
  *(volatile int*)(param_1+0x374) = param_1 - 0x5c;
  if(*(volatile int*)(param_1-0x48)==0){
    if(*(volatile int*)0x2000230cUL > 2){
      if(*(volatile int*)0x20007554UL == 0){
        DEBUG_PRINT(0x000d723a, 0x000d72bb);
      } else {
        FUN_00019c70(0x000d723a, 0x000d72bb);
      }
    }
    FUN_00015df4();
    void (*fp)(int) = *(void(* volatile*)(int))(param_1-0x5c);
    fp(*(volatile int*)(param_1+0x374));
    FUN_00047538();
    *(volatile int*)(param_1+0x35c) = 1;
    int iVar1 = FUN_0001655c();
    if(iVar1==0){
      FUN_0002e67c();
    }
  }
  return 0;
}

