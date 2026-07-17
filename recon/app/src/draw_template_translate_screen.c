/* Reconstructed draw_template_translate_screen @ 0x3fd44  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern int  FUN_000167a8(void);
extern void FUN_00019c70(int,int,...);
extern void FUN_000431b4(int);
extern void FUN_00043484(int,int,int,int,int,int);
extern void FUN_00043e90(int,int,int,int,int,int,int,int,int,int,int,int);
extern void FUN_000442bc(int,int,int,int,int,int,int);
extern void FUN_00077914(int*,int,int,int,int);
extern int  FUN_0007d224(void);
extern int  FUN_0007d3ee(void);
extern int  FUN_0007d446(void);
#define VI(a) (*(volatile int*)(a))

int draw_template_translate_screen(int param_1){
  volatile int *lvl=(volatile int*)0x2000230cUL;
  volatile int *g8=(volatile int*)0x20007554UL;
  int iVar1,iVar4,iVar5,iVar6,iVar7,uVar2,uVar3;
  unsigned int uVar8,uVar9;
  int local_24[3];
  iVar1 = FUN_000167a8();
  FUN_000431b4(param_1 + 0x24);
  uVar8 = *(volatile unsigned char*)(iVar1+0xf0);
  uVar9 = (unsigned int)(*(volatile unsigned char*)(iVar1+0xef) - 1);
  if (uVar8 < 9 && (uVar9 & 0xff) < 8 && uVar8 != 0) {
    local_24[0]=0; local_24[1]=0; local_24[2]=0;
    FUN_00077914(local_24, 10, 0x000aa4ea,
                 VI(0x200024f4 + (uVar8-1)*4), VI(0x200024f4 + uVar9*4));
    uVar2 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar6 = FUN_0007d446();
    FUN_00043e90(0,(int)local_24,3,uVar2,iVar4+0x6e,iVar5+0x50,iVar6+0x89,1,0,0,0,0);
  } else if (0 < *lvl) {
    if (*g8==0) DEBUG_PRINT(0x000aa487,0x000aa5ab,uVar8,*(volatile unsigned char*)(iVar1+0xef));
    else FUN_00019c70(0x000aa487,0x000aa5ab,uVar8,
                      *(volatile unsigned char*)(iVar1+0xef));
  }
  uVar2 = FUN_0007d224();
  uVar3 = FUN_0007d3ee();
  iVar4 = FUN_0007d446();
  iVar5 = FUN_0007d3ee();
  iVar6 = FUN_0007d446();
  FUN_000442bc(uVar2,uVar3,iVar4+2,iVar5+0x50,iVar6+0x1d,3,1);
  if (*(volatile char*)(iVar1+0xf1) == 1) {
    uVar2 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    uVar3 = 0x1b;
  } else {
    uVar2 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    uVar3 = 0x33;
  }
  FUN_00043484(uVar3,uVar2,iVar4+0x36,0,0,0);
  iVar4 = FUN_0007d3ee();
  iVar5 = FUN_0007d446();
  iVar6 = FUN_0007d3ee();
  iVar7 = FUN_0007d446();
  FUN_00043e90(0,iVar1+0xf5,0,iVar4+0x58,iVar5+1,iVar6+0x240,iVar7+0x88,5,0,0,0,0);
  return 0;
}
