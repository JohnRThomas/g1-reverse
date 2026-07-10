/* Reconstructed FUN_00031dd8 @ 0x31dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00022b00(unsigned,int);
extern int FUN_000232f8(void*);
extern void FUN_0007d14a(int);
extern void FUN_00086c78(void*,int,int);
extern void FUN_00086f00(void*,int,int,unsigned,int);
unsigned FUN_00031dd8(unsigned param_1, unsigned param_2, unsigned **param_3, unsigned char *param_4)
{
  int *piVar1; int iVar2, iVar4; unsigned uVar3; unsigned char *puVar5; unsigned char uVar6; char cVar7;
  unsigned local_b0; unsigned char auStack_ac[16]; unsigned char auStack_9c[12]; int local_90;
  DEBUG_PRINT(0x000a715d);
  if ((param_3 == 0) || (param_4 == 0)) { DEBUG_PRINT(0x000a7173); return 0xffffffff; }
  if (*(char*)0x20019ef3 != 1) { DEBUG_PRINT(0x000a672f); return 0xfffffffe; }
  puVar5 = (unsigned char*)*param_3;
  *(volatile unsigned char*)(puVar5) = 0x2d;
  *(volatile unsigned char*)(puVar5+2) = 3;
  *(volatile unsigned char*)(puVar5+3) = 5;
  *(volatile unsigned char*)(puVar5+1) = 1;
  piVar1 = (int*)0x20007aac;
  local_b0 = 0;
  FUN_00086c78(auStack_ac, 0, 0x10);
  if ((((*(int*)0x20007aa8 == 0 && *piVar1 == 0) && *(int*)0x20007aa4 == 0) &&
       (iVar2 = FUN_000167a8(), *(int*)(iVar2+0x107c) == 0)) &&
      (iVar2 = FUN_000167a8(), *(int*)(iVar2+0x1080) == 0)) {
    iVar2 = FUN_000167a8();
    uVar6 = 1;
    if (*(int*)(iVar2+0x1084) == 0) goto LAB_6e;
  }
  iVar2 = FUN_000167a8();
  uVar6 = 0;
  *(volatile int*)(iVar2+0xf64) = *piVar1;
LAB_6e:
  iVar2 = *piVar1;
  *(volatile unsigned char*)(puVar5+4) = uVar6;
  FUN_00086f00(&local_b0, 0, 0x14, 0x0009ddbf, iVar2);
  iVar2 = FUN_000167a8();
  cVar7 = 0;
  *(volatile unsigned*)(puVar5+5) = *(unsigned*)(iVar2+0xf64);
  uVar3 = FUN_000167a8();
  FUN_00022b00(uVar3, 0);
  iVar2 = FUN_000167a8();
  iVar2 = *(int*)(iVar2+0xf64);
  do {
    iVar4 = FUN_000232f8(auStack_9c);
    if ((iVar4 == 0) && (local_90 == iVar2)) goto LAB_c0;
    cVar7 = cVar7 + 1;
    FUN_0007d14a(100);
  } while (cVar7 != 5);
  *(volatile unsigned char*)(puVar5+4) = 2;
LAB_c0:
  *(volatile unsigned char*)param_4 = 9;
  return 0;
}

