/* Reconstructed FUN_00068f94 @ 0x68f94  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char undefined1; typedef unsigned int uint;
extern int FUN_00086c78(int,...);

undefined1 * FUN_00068f94(int param_1,int param_2,int param_3,undefined1 *param_4)
{
  long long lVar1; int iVar2=0; uint uVar3; int iVar4; int iVar5=0; int iVar6;
  undefined1 *puVar7; uint uVar8=0; uint uVar9=0;
  if (param_3 < 1) param_3 = param_2;
  if (param_1 == 0x1d4c) {
    if (param_2 == 8000) {
      if (param_3 == 8000) { iVar2=0; uVar3=3; iVar5=0; uVar8=0; uVar9=0; }
      else {
        if (param_3 == 16000) uVar9=1;
        else if (param_3 == 24000) uVar9=2;
        else {
          if (param_3 != 32000) {
            if (param_3 != 48000) return (undefined1*)0;
            iVar5=0; iVar2=1; uVar3=3; uVar9=4; uVar8=0; goto LAB_9026;
          }
          uVar9=3;
        }
        iVar2=0; uVar3=3; iVar5=0; uVar8=0;
      }
      goto LAB_9026;
    }
    uVar3=3; iVar5=0;
  } else if (param_1 == 10000) {
    if (param_2 == 8000) {
      if (param_3 == 8000) { iVar2=0; uVar3=4; iVar5=1; uVar8=0; uVar9=0; }
      else if (param_3 == 16000) { iVar2=0; iVar5=1; uVar3=4; uVar8=0; uVar9=1; }
      else {
        if (param_3 == 24000) uVar9=2;
        else {
          if (param_3 != 32000) {
            if (param_3 != 48000) return (undefined1*)0;
            iVar2=1; uVar3=4; uVar8=0; iVar5=iVar2; uVar9=uVar3; goto LAB_9026;
          }
          uVar9=3;
        }
        iVar2=0; uVar3=4; iVar5=1; uVar8=0;
      }
      goto LAB_9026;
    }
    uVar3=4; iVar5=1;
  } else {
    if (param_2 == 8000) return (undefined1*)0;
    uVar3=5; iVar5=2;
  }
  if (param_2 == 16000) {
    if (param_3 == 8000) return (undefined1*)0;
    uVar9=1; uVar8=1;
    if (param_3 == 16000) goto LAB_9106;
LAB_8ffe:
    uVar8=uVar9;
    if (param_3 == 24000) { if (iVar5==2) return (undefined1*)0; iVar2=0; uVar9=2; }
    else if (param_3 == 32000) { if (iVar5==2) return (undefined1*)0; iVar2=0; uVar9=3; }
    else {
      if (param_3 != 48000) return (undefined1*)0;
      if (iVar5==2) return (undefined1*)0;
      iVar2=1; uVar9=4;
    }
  } else {
    if (param_2 == 24000) { if (param_3==8000) return (undefined1*)0; uVar8=2; }
    else if (param_2 == 32000) { if (param_3==8000) return (undefined1*)0; uVar8=3; }
    else if (param_2 == 48000) { if (param_3==8000) return (undefined1*)0; uVar8=4; }
    else { if (param_3==8000) return (undefined1*)0; uVar8=5; }
    uVar9=uVar8;
    if (param_3 != 16000) goto LAB_8ffe;
LAB_9106:
    if (iVar5==2) return (undefined1*)0;
    iVar2=0; uVar9=1;
  }
  if (uVar9 < uVar8) return (undefined1*)0;
LAB_9026:
  if (param_4 == (undefined1*)0) return (undefined1*)0;
  iVar6 = uVar8 + 1;
  if (uVar8 == 4) iVar6 = 6;
  iVar4 = (iVar2 + uVar9) * uVar3 + uVar3;
  FUN_00086c78((int)param_4,0,0x4b0);
  iVar2 = iVar6 * 10 + iVar4 * 0x14 >> 1;
  *param_4 = (char)iVar5;
  puVar7 = param_4 + 0x4ac;
  *(undefined1 **)(param_4 + 0x4a8) = puVar7 + (iVar4 * 0x14 + iVar2) * 4;
  *(undefined1 **)(param_4 + 0x4a4) = puVar7 + iVar2 * 4;
  iVar5 = (int)((long long)(int)0x431bde83 * (long long)(param_1 * param_3) >> 0x32) -
          (param_1 * param_3 >> 0x1f);
  lVar1 = (long long)(int)0x51eb851f;
  param_4[1] = (char)uVar8;
  param_4[2] = (char)uVar9;
  *(undefined1 **)(param_4 + 0x4a0) = puVar7 + iVar6 * 0x14;
  if (param_1 == 0x1d4c) {
    iVar2 = iVar5 * 0x17;
    iVar2 = ((int)((unsigned long long)((long long)(int)0x88888889 * (long long)iVar2) >> 0x20) + iVar2 >> 4) -
            (iVar2 >> 0x1f);
  } else {
    iVar2 = iVar5 * 5;
    if (iVar2 < 0) iVar2 = iVar2 + 7;
    iVar2 = iVar2 >> 3;
  }
  FUN_00086c78((int)puVar7,0,(iVar5 + (((int)(lVar1 * param_3 >> 0x28) - (param_3 >> 0x1f)) + iVar5) / 2
                        + iVar2) * 4);
  return param_4;
}

