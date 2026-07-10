#include "g1_app_symbols.h"
/* named: cjson_parse_value */
/* Reconstructed cjson_parse_value @ 0x12910  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned char byte; typedef unsigned long long undefined8;
extern int __aeabi_dcmple(int,...); extern int __aeabi_dcmpge(int,...); extern int __fixdfsi(int,...);
extern int cjson_parse_string(int,...); extern int cjson_delete(int,...); extern unsigned long long FUN_00077a10(int,...);
extern int FUN_00084ed8(int,...); extern int alloc_zeroed_node(int,...); extern int strncmp(int,...);

undefined4 cjson_parse_value(int param_1,int *param_2)
{
  char cVar1; byte bVar2; int iVar3; undefined4 uVar4; int *piVar5; byte *pbVar6; uint uVar7;
  uint uVar8; int *piVar9; int iVar10; int *piVar11; int *piVar12; uint uVar13; byte *pbVar14;
  int bVar15; unsigned long long uVar16; byte *local_64; byte abStack_60[64]; undefined4 uVar17;
  if (param_2 == 0) return 0;
  iVar10 = *param_2;
  if (iVar10 == 0) return 0;
  uVar8 = param_2[2]; uVar13 = param_2[1];
  if (uVar13 < uVar8 + 4) {
    if (uVar8 + 5 <= uVar13) {
LAB_74:
      iVar3 = strncmp(iVar10 + uVar8,"false" /*=0xf698e*/,5);
      if (iVar3 == 0) { *(undefined4 *)(param_1 + 0xc) = 1; pbVar6 = (byte *)(param_2[2] + 5); goto LAB_88; }
      if (uVar8 + 4 <= uVar13) goto LAB_92;
    }
LAB_52:
    if (uVar13 <= uVar8) return 0;
    uVar7 = (uint)*(byte *)(iVar10 + uVar8);
    if (uVar7 == 0x22) { uVar4 = cjson_parse_string(param_1,param_2); return uVar4; }
    if ((uVar7 == 0x2d) || (uVar7 - 0x30 < 10)) {
      iVar3 = 0; local_64 = (byte *)0x0; pbVar6 = (byte *)(iVar10 + uVar8); pbVar14 = abStack_60;
      do {
        bVar2 = *pbVar6;
        if (bVar2 < 0x46) {
          if (bVar2 < 0x2b) goto LAB_fa;
          if ((1 << (uint)(byte)(bVar2 - 0x2b) & 0x04007fe5) == 0) { bVar15 = bVar2 == 0x2e; goto LAB_ea; }
        } else {
          bVar15 = bVar2 == 0x65;
LAB_ea:
          if (!bVar15) goto LAB_fa;
        }
        iVar3 = iVar3 + 1; *pbVar14 = bVar2;
        if ((iVar3 == 0x3f) || (pbVar6 = pbVar6 + 1, pbVar14 = pbVar14 + 1, iVar3 == (int)(uVar13 - uVar8))) goto LAB_fa;
      } while (1);
    }
    if (uVar7 == 0x5b) {
      uVar7 = param_2[3];
      if (999 < uVar7) return 0;
      param_2[3] = uVar7 + 1;
      if (*(char *)(iVar10 + uVar8) != '[') return 0;
      param_2[2] = uVar8 + 1; FUN_00084ed8((int)param_2); uVar8 = param_2[2];
      if (uVar13 <= uVar8) { LAB_a9a: param_2[2] = uVar8 - 1; return 0; }
      if (*(char *)(iVar10 + uVar8) == ']') { piVar11 = (int *)0x0; param_2[3] = uVar7; }
      else {
        param_2[2] = uVar8 - 1; piVar9 = (int *)0x0; piVar12 = (int *)0x0;
        do {
          piVar5 = (int *)alloc_zeroed_node(param_2[4]); piVar11 = piVar12;
          if (piVar5 == 0) goto LAB_c08;
          piVar11 = piVar5;
          if (piVar12 != 0) { *piVar9 = (int)piVar5; piVar5[1] = (int)piVar9; piVar11 = piVar12; }
          param_2[2] = param_2[2] + 1; FUN_00084ed8((int)param_2);
          iVar10 = cjson_parse_value((int)piVar5,param_2);
          if (iVar10 == 0) goto LAB_c08;
          FUN_00084ed8((int)param_2);
          if ((uint)param_2[1] <= (uint)param_2[2]) goto LAB_c0e;
          cVar1 = *(char *)(*param_2 + param_2[2]); piVar9 = piVar5; piVar12 = piVar11;
        } while (cVar1 == ',');
        if (cVar1 != ']') { LAB_c0e: cjson_delete((int)piVar11); return 0; }
        param_2[3] = param_2[3] + -1; piVar11[1] = (int)piVar5;
      }
      uVar4 = 0x20;
    } else {
      if (uVar7 != 0x7b) return 0;
      uVar7 = param_2[3];
      if (999 < uVar7) return 0;
      param_2[3] = uVar7 + 1;
      if (*(char *)(iVar10 + uVar8) != '{') return 0;
      param_2[2] = uVar8 + 1; FUN_00084ed8((int)param_2); uVar8 = param_2[2];
      if (uVar13 <= uVar8) goto LAB_a9a;
      if (*(char *)(iVar10 + uVar8) == '}') { piVar11 = (int *)0x0; param_2[3] = uVar7; }
      else {
        param_2[2] = uVar8 - 1; piVar9 = (int *)0x0; piVar12 = (int *)0x0;
        do {
          piVar5 = (int *)alloc_zeroed_node(param_2[4]); piVar11 = piVar12;
          if (piVar5 == 0) goto LAB_c08;
          piVar11 = piVar5;
          if (piVar12 != 0) { *piVar9 = (int)piVar5; piVar5[1] = (int)piVar9; piVar11 = piVar12; }
          param_2[2] = param_2[2] + 1; FUN_00084ed8((int)param_2);
          iVar10 = cjson_parse_string((int)piVar5,param_2);
          if (iVar10 == 0) goto LAB_c08;
          FUN_00084ed8((int)param_2);
          iVar10 = piVar5[4]; piVar5[4] = 0; piVar5[8] = iVar10; uVar8 = param_2[2];
          if (((uint)param_2[1] <= uVar8) || (*(char *)(*param_2 + uVar8) != ':')) goto LAB_c08;
          param_2[2] = uVar8 + 1; FUN_00084ed8((int)param_2);
          iVar10 = cjson_parse_value((int)piVar5,param_2);
          if (iVar10 == 0) goto LAB_c08;
          FUN_00084ed8((int)param_2);
          if ((uint)param_2[1] <= (uint)param_2[2]) goto LAB_c0e;
          cVar1 = *(char *)(*param_2 + param_2[2]); piVar9 = piVar5; piVar12 = piVar11;
        } while (cVar1 == ',');
        if (cVar1 != '}') goto LAB_c0e;
        param_2[3] = param_2[3] + -1; piVar11[1] = (int)piVar5;
      }
      uVar4 = 0x40;
    }
    *(int **)(param_1 + 8) = piVar11;
    *(undefined4 *)(param_1 + 0xc) = uVar4;
    pbVar6 = (byte *)(param_2[2] + 1);
  } else {
    iVar3 = strncmp(iVar10 + uVar8,"null" /*=0xf6977*/,4);
    if (iVar3 == 0) { *(undefined4 *)(param_1 + 0xc) = 4; }
    else {
      if (uVar8 + 5 <= uVar13) goto LAB_74;
LAB_92:
      iVar3 = strncmp(iVar10 + uVar8,"true" /*=0xf6994*/,4);
      if (iVar3 != 0) goto LAB_52;
      *(undefined4 *)(param_1 + 0xc) = 2; *(undefined4 *)(param_1 + 0x14) = 1;
    }
    pbVar6 = (byte *)(param_2[2] + 4);
  }
LAB_88:
  param_2[2] = (int)pbVar6;
  return 1;
LAB_fa:
  abStack_60[iVar3] = 0;
  uVar16 = FUN_00077a10((int)abStack_60,(int)&local_64);
  pbVar6 = local_64;
  uVar17 = (undefined4)(uVar16 >> 0x20); uVar4 = (undefined4)uVar16;
  if (local_64 == abStack_60) return 0;
  iVar10 = __aeabi_dcmpge(uVar4,uVar17,0,0);
  if (iVar10 == 0) {
    iVar10 = __aeabi_dcmple(uVar4,uVar17,0,0xc1e00000);
    if (iVar10 == 0) uVar4 = __fixdfsi(uVar4,uVar17);
    else uVar4 = 0x80000000;
  } else uVar4 = 0x7fffffff;
  *(undefined8 *)(param_1 + 0x18) = uVar16;
  *(undefined4 *)(param_1 + 0x14) = uVar4;
  *(undefined4 *)(param_1 + 0xc) = 8;
  pbVar6 = pbVar6 + (param_2[2] - (int)abStack_60);
  goto LAB_88;
LAB_c08:
  if (piVar11 == 0) return 0;
  goto LAB_c0e;
}

