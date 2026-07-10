/* named: stream_flash_flush_buffer */
/* Reconstructed stream_flash_flush_buffer @ 0x4e1ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned,unsigned,void*,int);
extern int FUN_0004e124(int*,int);
extern unsigned FUN_0007f064(int);
extern void memset_bytes(int,int,int);
typedef int (*cf)(int,int,int,int);
int stream_flash_flush_buffer(int *param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
  int iVar1, iVar3, iVar5; unsigned uVar2, uVar4;
  unsigned local_28, local_24; int iStack_20, local_1c, uStack_18;
  if (param_1[2] == 0) return 0;
  iVar5 = param_1[5] + param_1[4];
  uStack_18 = param_4;
  iVar1 = FUN_0004e124(param_1, param_1[2] + -1 + iVar5);
  local_24 = 0x000f1052;
  if (-1 < iVar1) {
    uVar2 = FUN_0007f064(param_1[3]);
    iVar1 = param_1[2] - uVar2 * ((unsigned)param_1[2] / uVar2);
    if (iVar1 != 0) {
      iVar1 = uVar2 - iVar1;
      iVar3 = (*(cf*)(*(int*)(param_1[3] + 8) + 0xc))(0,0,0,0);
      memset_bytes(*param_1 + param_1[2], *(unsigned char*)(iVar3 + 4), iVar1);
    }
    iVar1 = (*(cf*)(*(int*)(param_1[3] + 8) + 4))(param_1[3], iVar5, *param_1, param_1[2] + iVar1);
    local_24 = 0x000f1080;
    if (iVar1 == 0) {
      uVar2 = 0;
      if (param_1[7] == 0) {
LAB:
        param_1[4] = param_1[4] + param_1[2];
        param_1[2] = 0;
        return 0;
      }
      for (; uVar2 < (unsigned)param_1[2]; uVar2 = uVar2 + 1) {
        *(unsigned char*)(*param_1 + uVar2) = ~*(unsigned char*)(*param_1 + uVar2);
      }
      iVar1 = (*(cf*)**(int**)(param_1[3] + 8))(param_1[3], iVar5, 0, 0);
      local_24 = 0x000f10a4;
      if ((iVar1 == 0) &&
          (iVar1 = (*(cf*)param_1[7])(*param_1, param_1[2], iVar5, 0), local_24 = 0x000f10ba, iVar1 == 0)) goto LAB;
      local_28 = 3; uVar4 = 0x1840; goto LAB2;
    }
  }
  local_28 = 4; uVar4 = 0x2040; local_1c = iVar5;
LAB2:
  iStack_20 = iVar1;
  FUN_0004d944(0x000880d8, uVar4, &local_28, 0);
  return iVar1;
}

