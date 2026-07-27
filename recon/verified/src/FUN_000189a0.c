/* Reconstructed FUN_000189a0 @ 0x189a0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern unsigned FUN_0007f4c8(unsigned callback_object);
extern unsigned FUN_0007f4cc(unsigned);
extern int FUN_0007f8dc(unsigned,unsigned);
extern int FUN_0004f418(unsigned,unsigned);
extern int FUN_0007f594(unsigned);
extern void FUN_000187e8(unsigned,int);
void FUN_000189a0(unsigned param_1, unsigned param_2){
  unsigned uVar1, uVar2; int iVar3; unsigned fmt;
  uVar1 = FUN_0007f4c8(param_1);
  uVar2 = FUN_0007f4cc(param_1);
  if(uVar2 < 2){ DEBUG_PRINT(0x9a8c3); }
  else {
    DEBUG_PRINT(0x9a820);
    iVar3 = FUN_0007f8dc(param_1,param_2);
    fmt = 0x9a854;
    if(iVar3!=0 || (iVar3=FUN_0004f418(param_2,0x18a39), fmt=0x9a88a, iVar3!=0)){
      DEBUG_PRINT(fmt,iVar3);
    }
  }
  iVar3 = FUN_0007f594(param_1);
  if(iVar3!=0){ DEBUG_PRINT(0x9a7bc,iVar3); }
  FUN_000187e8(uVar1,0);
  return;
}
