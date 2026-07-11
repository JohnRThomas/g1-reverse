/* Reconstructed FUN_000188d8 @ 0x188d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_000187e8(int,...);
extern int FUN_0004ee68(int,...);
extern int FUN_0004f040(int,...);
extern int FUN_0004f0ec(int,...);
extern int FUN_0007c08e(int,...);
extern int FUN_0007f4c8(int callback_object);
extern int FUN_0007f594(int,...);
void FUN_000188d8(void *param_1, void *param_2){
  int uVar1 = FUN_0007f4c8((int)param_1);
  DEBUG_PRINT(0x9a6f2);
  int iVar2 = FUN_0004ee68((int)param_1,(int)param_2);
  unsigned fmt = 0x9a71e;
  if(iVar2==0){
    *(volatile uint32_t*)0x20006ab4UL |= 2u;
    iVar2 = FUN_0004f040((int)param_2, 0x18ef5);
    if(iVar2!=0) DEBUG_PRINT(0x9a74c, iVar2);
    iVar2 = FUN_0004f0ec((int)param_2, 0x18c49);
    fmt = 0x9a788;
    if(iVar2==0) goto L;
  }
  DEBUG_PRINT(fmt, iVar2);
L:
  iVar2 = FUN_0007f594((int)param_1);
  if(iVar2!=0) DEBUG_PRINT(0x9a7bc, iVar2);
  FUN_0007c08e(0x20006ab4, 0xfffffffe);
  FUN_000187e8(uVar1, 1);
}
