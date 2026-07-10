/* named: stdio_flush_write_buffer */
/* Reconstructed stdio_flush_write_buffer @ 0x86a0e  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int heap_free_core(int,...);
typedef int (*codeptr)(int,...);
unsigned int stdio_flush_write_buffer(int *param_1,int *param_2)
{
  int iVar1,iVar4,iVar7;
  int *piVar2;
  unsigned int uVar3;
  unsigned short uVar5;
  codeptr pcVar6;
  uVar3 = (unsigned int)(short)param_2[3];
  if ((int)(uVar3 << 0x1c) < 0) {
    iVar1 = param_2[4];
    if (iVar1 == 0) return 0;
    iVar7 = *param_2;
    *param_2 = iVar1;
    if ((uVar3 & 3) == 0) iVar4 = param_2[5];
    else iVar4 = 0;
    iVar7 = iVar7 - iVar1;
    param_2[2] = iVar4;
    while (1) {
      if (iVar7 < 1) return 0;
      iVar4 = ((codeptr)param_2[10])((int)param_1,param_2[8],iVar1,iVar7);
      if (iVar4 < 1) break;
      iVar1 = iVar1 + iVar4;
      iVar7 = iVar7 - iVar4;
    }
    uVar5 = *(unsigned short *)(param_2 + 3);
    *(unsigned short *)(param_2 + 3) = uVar5 | 0x40;
    return 0xffffffff;
  }
  if ((param_2[1] < 1) && (param_2[0x10] < 1)) return 0;
  pcVar6 = (codeptr)param_2[0xb];
  if (pcVar6 == 0) return 0;
  iVar7 = *param_1;
  iVar1 = param_2[8];
  *param_1 = 0;
  if ((uVar3 & 0x1000) == 0) {
    iVar1 = pcVar6((int)param_1,iVar1,0,1);
    if ((iVar1 == -1) && (iVar4 = *param_1, iVar4 != 0)) {
      if ((iVar4 == 0x1d) || (iVar4 == 0x16)) { *param_1 = iVar7; return 0; }
      uVar5 = *(unsigned short *)(param_2 + 3);
      *(unsigned short *)(param_2 + 3) = uVar5 | 0x40;
      return 0xffffffff;
    }
  } else {
    iVar1 = param_2[0x15];
  }
  if (((int)((unsigned int)*(unsigned short *)(param_2 + 3) << 0x1d) < 0) &&
      (iVar1 = iVar1 - param_2[1], param_2[0xd] != 0)) {
    iVar1 = iVar1 - param_2[0x10];
  }
  iVar1 = ((codeptr)param_2[0xb])((int)param_1,param_2[8],iVar1,0);
  if (iVar1 == -1) {
    iVar4 = *param_1;
    uVar5 = *(unsigned short *)(param_2 + 3);
    uVar3 = (unsigned int)(short)uVar5;
    if (iVar4 != 0) {
      if ((iVar4 != 0x1d) && (iVar4 != 0x16)) {
        *(unsigned short *)(param_2 + 3) = uVar5 | 0x40;
        return 0xffffffff;
      }
      param_2[1] = 0;
      *param_2 = param_2[4];
      goto LAB_00086a70;
    }
    param_2[1] = 0;
    *param_2 = param_2[4];
  } else {
    param_2[1] = 0;
    *param_2 = param_2[4];
    uVar3 = (unsigned int)*(unsigned short *)(param_2 + 3);
  }
  if ((int)(uVar3 << 0x13) < 0) param_2[0x15] = iVar1;
LAB_00086a70:
  piVar2 = (int *)param_2[0xd];
  *param_1 = iVar7;
  if (piVar2 != (int *)0) {
    if (piVar2 != param_2 + 0x11) heap_free_core((int)param_1);
    param_2[0xd] = 0;
  }
  return 0;
}

