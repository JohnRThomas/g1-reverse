/* Reconstructed set_brightness_lum_base @ 0x31cbc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned,...);
extern void FUN_00022b00(unsigned,int);
extern int FUN_000232f8(void*);
extern void FUN_0007d14a(int);
unsigned set_brightness_lum_base(int param_1, unsigned param_2, unsigned **param_3, unsigned char *param_4)
{
  char cVar2, cVar9; unsigned char bVar1; unsigned short uVar3; int *piVar4; unsigned uVar5;
  int iVar6; unsigned uVar7, uVar8; unsigned char *puVar10;
  unsigned char auStack_9c[116];
  unsigned short local_28, local_26, local_24;
  DEBUG_PRINT(0x000a70a0);
  if ((param_3 == 0) || (param_4 == 0)) {
    DEBUG_PRINT(0x000a70c1);
    uVar5 = 0xffffffff;
  } else if (*(char*)0x20019ef3 == 1) {
    puVar10 = (unsigned char*)*param_3;
    *(volatile unsigned char*)(puVar10) = 0x36;
    *(volatile unsigned char*)(puVar10+2) = 3;
    *(volatile unsigned char*)(puVar10+3) = 2;
    piVar4 = (int*)0x2000230c;
    *(volatile unsigned char*)(puVar10+1) = 1;
    cVar2 = *(char*)(param_1 + 4);
    uVar8 = (unsigned)*(unsigned short*)(param_1 + 5);
    if (2 < *piVar4) {
      if (*(int*)0x20007554 == 0) DEBUG_PRINT(0x000a70e7, 0x000a7655, uVar8);
      else FUN_00019c70(0x000a70e7, 0x000a7655, uVar8);
    }
    bVar1 = 0x3f < uVar8;
    if (bVar1) uVar8 = 0x3f;
    *(volatile unsigned char*)(puVar10+4) = bVar1;
    uVar3 = (unsigned short)uVar8;
    if (cVar2 == 1) { iVar6 = FUN_000167a8(); *(volatile unsigned short*)(iVar6 + 0xedc) = uVar3; }
    else if (cVar2 == 2) { iVar6 = FUN_000167a8(); *(volatile unsigned short*)(iVar6 + 0xede) = uVar3; }
    else if (cVar2 == 0) { iVar6 = FUN_000167a8(); *(volatile unsigned short*)(iVar6 + 0xeda) = uVar3; }
    iVar6 = FUN_000167a8(); *(volatile unsigned short*)(iVar6 + 0xed8) = uVar3;
    uVar5 = FUN_000167a8(); FUN_00022b00(uVar5, 0);
    cVar9 = 0;
    do {
      iVar6 = FUN_000232f8(auStack_9c);
      if (iVar6 == 0) {
        if (cVar2 == 0) uVar7 = (unsigned)local_28;
        else if (cVar2 == 1) uVar7 = (unsigned)local_26;
        else { if (cVar2 != 2) goto LAB_6a; uVar7 = (unsigned)local_24; }
        if (uVar7 == uVar8) goto LAB_7c;
      }
LAB_6a:
      cVar9 = cVar9 + 1;
      FUN_0007d14a(100);
    } while (cVar9 != 5);
    *(volatile unsigned char*)(puVar10+4) = 2;
LAB_7c:
    *(volatile unsigned char*)(puVar10+5) = cVar2;
    uVar5 = 0;
    *(volatile unsigned char*)param_4 = 6;
  } else {
    DEBUG_PRINT(0x000a672f);
    uVar5 = 0xfffffffe;
  }
  return uVar5;
}

