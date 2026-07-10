/* Reconstructed FUN_0004a890 @ 0x4a890  (parity: 300/300 trials, PROVEN) */
extern int FUN_000167a8(void);
extern unsigned FUN_0007dac0(void);
extern unsigned long long FUN_0007daa4(void);
extern void DEBUG_PRINT(int,...);
extern void FUN_00019c70(int,...);
void FUN_0004a890(void){
  int iVar1; unsigned uVar2; unsigned long long uVar3;
  iVar1 = FUN_000167a8();
  if (*(volatile unsigned char*)(iVar1+0x10ac) != 1){
    uVar2 = FUN_0007dac0();
    if (uVar2 < 7){
      iVar1 = FUN_000167a8();
      *(volatile unsigned char*)(iVar1+0x10ac) = 1;
      iVar1 = FUN_000167a8();
      *(volatile unsigned char*)(iVar1+0x10ad) = (unsigned char)uVar2;
      iVar1 = FUN_000167a8();
      uVar3 = FUN_0007daa4();
      *(volatile unsigned*)(iVar1+0x10b2) = (unsigned)(uVar3>>32);
      *(volatile unsigned*)(iVar1+0x10ae) = (unsigned)uVar3;
      iVar1 = FUN_000167a8();
      iVar1 = uVar2*0xc + iVar1;
      *(volatile int*)(iVar1+0x10e6) = *(volatile int*)(iVar1+0x10e6) + 1;
      iVar1 = FUN_000167a8();
      *(volatile int*)(iVar1+0x10ce) = *(volatile int*)(iVar1+0x10ce) + 1;
      if (1 < *(volatile int*)0x2000230cUL){
        if (*(volatile int*)0x20007554UL != 0){
          iVar1 = FUN_000167a8();
          FUN_00019c70(0x000f0337,0x000f04a9,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
          return;
        }
        iVar1 = FUN_000167a8();
        DEBUG_PRINT(0x000f0337,0x000f04a9,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
        return;
      }
    }
  }
  return;
}

