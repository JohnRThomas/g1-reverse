#include "g1_net_symbols.h"
/* net-core FUN_01010578 @ 0x1010578  (parity 300 trials PROVEN) */
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned long long undefined8;
typedef unsigned long long ulonglong;
typedef unsigned short undefined2;

extern int FUN_0100d760(void);
extern void FUN_0100ef48(int, undefined4);
extern void FUN_0100ef88(int, undefined4, int, undefined4);
extern undefined1 FUN_0102029c(void);
extern undefined8 thunk_FUN_01025034(void);

#define DAT_010106d0 ((char *)((uintptr_t)&g_sdc_rssi_filter_cfg) /*=0x21000f04*/)
#define DAT_010106d4 ((undefined4)((uintptr_t)&rodata_1010c61) /*=0x1010c61*/)
#define DAT_010106d8 ((undefined4)((uintptr_t)&rodata_1010c71) /*=0x1010c71*/)

void FUN_01010578(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  undefined2 *puVar12;
  undefined8 uVar13;

  puVar12 = *(undefined2 **)(param_1 + 4);
  iVar5 = FUN_0100d760();
  cVar1 = *param_1;
  iVar11 = *(int *)(param_1 + 4);
  *(char *)(iVar11 + 0xc1) = (char)iVar5;
  pcVar2 = DAT_010106d0;
  if (cVar1 == '\0') {
    if (iVar5 == 0x7f) {
      return;
    }
    iVar10 = iVar5 * (0x1000 - *(int *)(DAT_010106d0 + 8)) +
             (*(int *)(DAT_010106d0 + 8) * *(int *)(iVar11 + 0xb0) >> 0xc);
  }
  else {
    if (iVar5 == 0x7f) {
      return;
    }
    iVar10 = iVar5 * (0x1000 - *(int *)(DAT_010106d0 + 8)) +
             (*(int *)(iVar11 + 0xb0) * *(int *)(DAT_010106d0 + 8) >> 0xc);
  }
  *(int *)(iVar11 + 0xb0) = iVar10;
  *(undefined1 *)(iVar11 + 0xc2) = *(undefined1 *)(iVar11 + 0xdb);
  if (pcVar2[0xc] != '\0') {
    iVar7 = (iVar10 + 0x800) * 0x1000 >> 0x18;
    if (iVar7 < *pcVar2) {
      cVar1 = pcVar2[1];
    }
    else {
      if (iVar7 <= pcVar2[2]) goto LAB_010105c8;
      cVar1 = pcVar2[3];
    }
    iVar10 = (int)(char)-(char)(iVar10 + 0x800 >> 0xc) + (int)cVar1;
    if ((((0xff < iVar10 + 0x80U) || ((char)iVar10 != '\0')) &&
        (*(int *)(iVar11 + 0xac) != 0x7fffffff || *(uint *)(iVar11 + 0xa8) != 0xffffffff)) &&
       (uVar13 = thunk_FUN_01025034(), uVar6 = (uint)((ulonglong)uVar13 >> 0x20),
       *(uint *)(iVar11 + 0xac) < uVar6 ||
       uVar6 - *(uint *)(iVar11 + 0xac) < (uint)(*(uint *)(iVar11 + 0xa8) <= (uint)uVar13))) {
      iVar10 = *(int *)(param_1 + 4);
      uVar4 = FUN_0102029c();
      uVar3 = DAT_010106d8;
      *(undefined1 *)(iVar10 + 0x6f) = uVar4;
      FUN_0100ef48(iVar10 + 600,uVar3);
    }
  }
LAB_010105c8:
  uVar9 = (short)iVar5 - (short)*(char *)(iVar11 + 0xc3);
  if ((short)uVar9 < 0) {
    uVar9 = -uVar9;
  }
  if (((*(byte *)(iVar11 + 0x2d) <= uVar9) && (*(byte *)(iVar11 + 0x2d) != 0xff)) &&
     ((bVar8 = *(char *)(iVar11 + 0xc4) + 1, *(byte *)(iVar11 + 0xc4) = bVar8,
      *(byte *)(iVar11 + 0x2e) < bVar8 || (*(char *)(iVar11 + 0xc3) == '\x7f')))) {
    *(char *)(iVar11 + 0xc3) = (char)iVar5;
    *(undefined1 *)(iVar11 + 0xc4) = 0;
    uVar3 = DAT_010106d4;
    if (*(char *)((char*)puVar12 + 0x16) == '\x01') {
      iVar5 = *(int *)(param_1 + 4);
      if (*(char *)(iVar5 + 0x1c0) == '\0') {
        *(undefined2 *)(iVar5 + 0x1c1) = *puVar12;
        *(undefined1 *)(iVar5 + 0x1c3) = *(undefined1 *)((int)puVar12 + 0xc1);
        *(undefined1 *)(iVar5 + 0x1c4) = *(undefined1 *)((char*)puVar12 + 0x61 * 2);
        FUN_0100ef88(iVar5 + 0x1b8,uVar3,2,param_4);
        return;
      }
    }
  }
  return;
}


