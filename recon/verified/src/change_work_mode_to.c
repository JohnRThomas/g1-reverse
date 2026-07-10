/* Reconstructed change_work_mode_to @ 0x1694c  (parity: 296/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...);
extern int FUN_000167f4(int,...);
extern int FUN_00016854(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_00025b78(int,...);
extern int FUN_0007c038(int,...);
extern int FUN_00086c78(int,...);

void change_work_mode_to(uint param_1){
  volatile char *pcVar1 = (volatile char*)0x2000ff4b;
  int *piVar2; int iVar4 = 3000; uint uVar3; int i;
  while ((piVar2 = (int*)0x200069fc, *pcVar1 != 0 && (iVar4 = iVar4 - 1, iVar4 != 0))) {
    FUN_0007c038(1);
  }
  *pcVar1 = 1;
  iVar4 = *piVar2;
  if ((uint)*(volatile byte*)(iVar4 + 1) != param_1) {
    *(volatile char*)(iVar4 + 1) = (char)param_1;
    if (0 < *(volatile int*)0x2000230c) {
      if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x9976b,0x99bb7,param_1 & 0xff);
      else FUN_00019c70(0);
    }
    uVar3 = *(volatile byte*)(*piVar2 + 1);
    if (uVar3 < 10) {
      switch (uVar3) {
        case 1: for(i=0;i<12;i++) FUN_00016854(0,0); break;
        case 2: for(i=0;i<11;i++) FUN_00016854(0,0); break;
        case 7: case 9: for(;;) FUN_00016854(0,0);
        default: for(i=0;i<10;i++) FUN_00016854(0,0); break;
      }
      *pcVar1 = 0;
      return;
    }
  }
  *pcVar1 = 0;
  return;
}

