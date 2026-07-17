/* Reconstructed FUN_000442bc @ 0x442bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef uint16_t undefined2; typedef unsigned int uint; typedef unsigned short ushort;
extern int DEBUG_PRINT(int,...);
extern int FUN_0000ef12(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_000431a8(int,...);
extern int FUN_00043e90(int,...);
extern int FUN_0004588c(int,...);
extern int FUN_000471cc(int,...);
extern int FUN_00047260(int,...);
extern int FUN_0004a1b8(int,...);
extern int FUN_0007d53a(int,...);
extern int FUN_00086f00(int,...);

undefined4 FUN_000442bc(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,char param_7)
{
  int *piVar1; int *piVar2; int iVar3; uint32_t iVar4; int iVar5; uint uVar6;
  short sVar7; undefined4 uVar8; byte *pbVar9; int iVar10;
  int local_50; int local_4c; undefined4 local_48;
  struct {
    undefined4 word_0;
    undefined2 half_4;
    ushort hour_6;
    uint minute_8;
    byte text_12[20];
  } display;

  display.word_0 = 0; display.half_4 = 0; display.hour_6 = 0; display.minute_8 = 0;
  FUN_0004a1b8(param_1,(int)&display.word_0);
  for (iVar10=0;iVar10<16;iVar10++) display.text_12[iVar10]=0;
  uVar6 = (uint)display.hour_6;
  if (param_7 == '\0') {
    if (uVar6 < 0xd) { if (uVar6 == 0) { display.hour_6 = 0xc; } }
    else { display.hour_6 = display.hour_6 - 0xc; }
    uVar6 = display.hour_6 / 10;
    sVar7 = display.hour_6 + (short)uVar6 * -10;
  } else {
    uVar6 = uVar6 / 10;
    sVar7 = display.hour_6 + (short)uVar6 * -10;
  }
  FUN_00086f00((int)display.text_12,0,0x10,0xaaaac,uVar6,sVar7,0xf02a3,
               (display.minute_8 & 0xffff) / 10,
               (display.minute_8 & 0xffff) % 10);
  iVar3 = FUN_0000ef12((int)display.text_12);
  switch(param_6) {
  case 0:
    uVar8 = 0;
    break;
  case 1:
    iVar4 = FUN_000431a8(0);
    if ((iVar4 & 2u) != 0) {
      FUN_000471cc(*(volatile int*)0x2000a034,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)0x20007554; piVar1 = (int*)0x2000230c;
    pbVar9 = display.text_12; iVar4 = param_2;
    for (iVar10 = 0; iVar3 != iVar10; iVar10 = iVar10 + 1) {
      local_50 = 0;
      iVar5 = FUN_0004588c(1,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      if ((iVar5 == 0) && (local_50 != 0)) {
        FUN_0007d53a(*(volatile int*)0x2000a034,local_50,local_4c / 2,local_48,iVar4,param_3);
        iVar4 = iVar4 + local_4c + 6;
      } else if (1 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7);
        } else { FUN_00019c70(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7); }
      }
      pbVar9 = pbVar9 + 1;
    }
    goto LAB_000443e4;
  case 2:
    iVar4 = FUN_000431a8(0);
    if ((iVar4 & 2u) != 0) {
      FUN_000471cc(*(volatile int*)0x2000a034,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)0x20007554; piVar1 = (int*)0x2000230c;
    iVar10 = 0; pbVar9 = display.text_12; iVar4 = param_2;
    while (iVar3 != iVar10) {
      local_50 = 0;
      iVar5 = FUN_0004588c(2,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      iVar10 = iVar10 + 1;
      if ((iVar5 == 0) && (local_50 != 0)) {
        FUN_0007d53a(*(volatile int*)0x2000a034,local_50,local_4c / 2,local_48,iVar4,param_3);
        if (pbVar9[1] == 0x3a) { iVar5 = local_4c + 7; } else { iVar5 = local_4c + 2; }
        iVar4 = iVar4 + iVar5;
        if (*pbVar9 == 0x3a) { iVar4 = iVar4 + 7; }
      } else if (1 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7);
        } else { FUN_00019c70(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7); }
      }
      pbVar9 = pbVar9 + 1;
    }
LAB_000443e4:
    iVar3 = FUN_000431a8(0);
    if ((((uint32_t)iVar3) & 2u) == 0) { return 0; }
    iVar3 = FUN_000167a8(0);
    uVar8 = *(undefined4 *)(iVar3 + 0xeb4);
    iVar3 = FUN_000167a8(0);
    FUN_00047260(uVar8,*(undefined4 *)(iVar3 + 0xeb8),param_2,param_3,param_4,param_5);
    return 0;
  case 3:
    uVar8 = 3;
    break;
  default:
    goto caseD_4;
  }
  FUN_00043e90(0,(int)display.text_12,uVar8,param_2,param_3,param_4,param_5,1,0,0,0,0);
caseD_4:
  (void)piVar1; (void)piVar2;
  return 0;
}
