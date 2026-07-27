/* Reconstructed convert_app_whitelist_to_json @ 0x352e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int  FUN_0000ef12(int);
extern int  FUN_00064b1c(int);
extern int  FUN_00064c8c(void);
extern int  FUN_00064ca4(void);
extern void FUN_00076d7c(int);
extern int  FUN_0008501a(int);
extern void FUN_00085046(int,int,int);
extern void FUN_0008504c(int,int,int);
extern void FUN_0008509e(int,int,void*);
extern void FUN_00086fee(int,int);
extern void thunk_FUN_00084f2e(int,int,const void *,unsigned int);

int convert_app_whitelist_to_json(int param_1,int param_2,int param_3){
  volatile int *g50 = (volatile int*)0x20007554UL;
  volatile unsigned char *pbVar1 = (volatile unsigned char*)0x2001a22cUL;
  int iVar3,iVar9=0,iVar4,iVar5; unsigned int uVar10,uVar8; int uVar6=0,uVar7=0,uVar2;
  iVar3 = param_1;
  if (param_1 == 0) { uVar6=0x1f1; iVar9=*g50; uVar7=0x000a88a9; goto final; }
  iVar9 = FUN_00064ca4();
  if (iVar9 == 0) { uVar6=0x1fa; iVar9=*g50; uVar7=0x000a88be; goto final; }
  FUN_0008504c(iVar9,0x000a862c,(*pbVar1)&1);
  FUN_0008504c(iVar9,0x000a864e,((unsigned int)*pbVar1<<0x1e)>>0x1f);
  FUN_0008504c(iVar9,0x000a869b,((unsigned int)*pbVar1<<0x1d)>>0x1f);
  FUN_0008504c(iVar9,0x000a866e,((unsigned int)*pbVar1<<0x1c)>>0x1f);
  iVar3 = FUN_00064ca4();
  if (iVar3 == 0) { uVar7=0x206; iVar3=*g50; uVar6=0x000a88d8; goto inner; }
  FUN_0008504c(iVar3,0x0009e235,((unsigned int)*pbVar1<<0x1b)>>0x1f);
  iVar4 = FUN_00064c8c();
  if (iVar4 == 0) { uVar7=0x20e; iVar3=*g50; uVar6=0x000a88f1; goto inner; }
  uVar10 = 0;
  for(;;){
    uVar8 = uVar10 & 0xff;
    if (pbVar1[1] <= uVar8) {
      FUN_00085046(iVar3,0x000f3630,iVar4);
      FUN_00085046(iVar9,0x0009e1b6,iVar3);
      uVar6 = FUN_0008501a(iVar9);
      if (*g50==0) DEBUG_PRINT(0x000a892b,uVar6); else FUN_00019c70(0x000a892b,uVar6);
      FUN_00086fee(param_1,uVar6);
      uVar2 = FUN_0000ef12(uVar6);
      FUN_00076d7c(uVar6);
      FUN_00064b1c(iVar9);
      return (unsigned short)uVar2;
    }
    iVar5 = FUN_00064ca4();
    uVar10 = uVar10 + 1;
    if (iVar5 == 0) break;
    FUN_0008509e(iVar5,0x0009a1dd,(void*)(pbVar1 + uVar8*0x38 + 2));
    FUN_0008509e(iVar5,0x000f33e4,(void*)(pbVar1 + uVar8*0x38 + 0x2a));
    thunk_FUN_00084f2e(iVar4,iVar5,
                       (const void *)(pbVar1 + uVar8*0x38 + 0x2a),uVar10);
  }
  uVar7=0x219; iVar3=*g50; uVar6=0x000a8912;
inner:
  if (iVar3 == 0) DEBUG_PRINT(uVar6,0x000a8a51,uVar7); else FUN_00019c70(uVar6,0x000a8a51,uVar7);
  FUN_00064b1c(iVar9);
  return 0;
final:
  if (iVar9 == 0) DEBUG_PRINT(uVar7,0x000a8a51,uVar6,iVar9,iVar3,param_2,param_3); else FUN_00019c70(uVar7,0x000a8a51,uVar6,iVar9,iVar3,param_2,param_3);
  return 0;
}
