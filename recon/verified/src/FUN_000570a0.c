/* Reconstructed FUN_000570a0 @ 0x570a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00018adc(void);
extern void FUN_000566a4(int);
extern int FUN_00057038(int,void*);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);
extern int FUN_000813b4(volatile unsigned*,unsigned);
extern void FUN_000813ca(unsigned,unsigned,void*);
extern void FUN_000817ea(int);

void FUN_000570a0(int param_1){
  int iVar5 = param_1 - 0x60;
  unsigned uVar1, uVar3;
  int iVar2;
  if(*(volatile char*)(param_1-0x53) == 0){
    FUN_000817ea(iVar5);
    for(iVar2 = *(volatile int*)0x2000ad1cUL;
        uVar1 = 0x00088058U, uVar3 = 0x00087fecU, iVar2 != 0;
        iVar2 = *(volatile int*)(iVar2+0x20)){
      if(*(void**)(iVar2+4) != 0)
        (*(void(**)(int,unsigned char))(iVar2+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
    }
    while(1){
      if(uVar1 < uVar3){
        FUN_0007e2fa(0x00099cbd,0x000f3a8d,0x000f3a5d,0x5fe);
        FUN_0007e2fa(0x000f0d20);
        FUN_0007e2ec(0x000f3a5d,0x5fe);
      }
      if(uVar1 <= uVar3) break;
      if(*(void**)(uVar3+4) != 0)
        (*(void(**)(int,unsigned char))(uVar3+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
      uVar3 = uVar3 + 0x24;
    }
    FUN_000566a4(iVar5);
    return;
  }
  if(*(volatile char*)(param_1-0x5e) != 1) return;
  volatile unsigned *puVar4 = (volatile unsigned*)(param_1-0x5c);
  unsigned local_20, local_1c, local_2c, local_30;
  int iStack_28;
  iVar2 = FUN_000813b4(puVar4, 0xfffffdffU);
  if((int)(iVar2 << 0x16) < 0){
    local_20 = *(volatile unsigned*)(param_1+0x48);
    local_1c = *(volatile unsigned*)(param_1+0x50);
    iStack_28 = FUN_00057038(iVar5,&local_20);
    local_2c = 0x000f3dff;
    if(iStack_28 == 0){
      FUN_000813b4(puVar4, 0xfffffeffU);
      goto LAB;
    }
  } else {
    local_20 = 0x00280018U;
    local_1c = 0x2a0000U;
    iStack_28 = FUN_00057038(iVar5,&local_20);
    local_2c = 0x000f3e24;
    if(iStack_28 == 0){
      *puVar4 = *puVar4 | 0x100;
      goto LAB;
    }
  }
  local_30 = 3;
  FUN_000813ca(0x00088108, 0x1880, &local_30);
LAB:
  *puVar4 = *puVar4 | 0x80;
  (void)local_2c; (void)local_1c;
  return;
}

