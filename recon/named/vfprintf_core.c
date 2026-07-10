/* named: vfprintf_core */
/* Reconstructed vfprintf_core @ 0x78f88  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte;
typedef unsigned int uint;

extern int FUN_00079278(int, void*, void*, void*);
extern int FUN_0007932c(int, void*, void*, void*);
extern int mem_find_byte(int, int, int);
extern void *stdio_reset_ungetc_buffer(void*, void*);
extern void *fnmatch_build_class_table(void*, void*);
typedef int (*fnptr)(int, void*);

int vfprintf_core(int param_1, int *param_2, byte *param_3, int *param_4)
{
  int iVar1 = 0xf8a6bL;
  int iVar2;
  int iVar3;
  uint uVar4, uVar5;
  byte *pbVar6;
  int *local_2a8;
  unsigned char auStack_2a4[256];
  uint local_1a4;
  int local_1a0;
  uint local_19c;
  int local_198 = 0;
  int local_194 = 0;
  unsigned char *local_190;
  int local_18c;
  int local_28;
  fnptr local_24;

  local_28 = 0x877ed;
  local_24 = (fnptr)0x87863UL;
  local_2a8 = param_4;
  local_190 = auStack_2a4;

LAB_00078fae:
  for (;;) {
    for (;;) {
      iVar2 = 0xf8b71L;
      uVar5 = (uint)*param_3;
      if (uVar5 == 0) return local_198;
      pbVar6 = param_3 + 1;
      uVar4 = (*(volatile byte*)(iVar1 + uVar5)) & 8;
      if (uVar4 == 0) break;
      param_3 = pbVar6;
      while (1) {
        if (!(0 < (int)param_2[1] || (iVar2 = local_24(param_1, param_2), iVar2 == 0))) break;
        if (!((int)((uint)(*(volatile byte*)(iVar1 + (uint)*(byte*)*param_2)) << 0x1c) < 0)) break;
        local_194 = local_194 + 1;
        *param_2 = *param_2 + 1;
        param_2[1] = param_2[1] - 1;
      }
    }
    if (uVar5 == 0x25) break;
  LAB_00078ff8:
    if (((int)param_2[1] < 1) && (iVar2 = local_24(param_1, param_2), iVar2 != 0))
      goto LAB_00079138;
    if (*(byte*)*param_2 != uVar5) return local_198;
    *param_2 = *param_2 + 1;
    param_2[1] = param_2[1] - 1;
    local_194 = local_194 + 1;
    param_3 = pbVar6;
  }
  local_1a4 = uVar4;
  local_19c = uVar4;
  if (param_3[1] == 0x2a) {
    local_1a4 = 0x10;
    pbVar6 = param_3 + 2;
  }
  for (;;) {
    uVar5 = (uint)*pbVar6;
    if (uVar5 - 0x30 > 9) break;
    local_19c = (local_19c * 10 + uVar5) - 0x30;
    pbVar6 = pbVar6 + 1;
  }
  iVar3 = mem_find_byte(0xf8b71L, uVar5, 3);
  if (iVar3 != 0) {
    local_1a4 = (1 << ((iVar3 - iVar2) & 0xffU)) | local_1a4;
    pbVar6 = pbVar6 + 1;
  }
  param_3 = pbVar6 + 1;
  uVar5 = (uint)*pbVar6;

  if (uVar5 < 0x79) {
    if (0x57 < uVar5) {
      switch (uVar5) {
        case 0x58: case 0x78:
          local_1a4 |= 0x200; local_1a0 = 0x10;
          goto SET_UO;
        case 0x5b:
          param_3 = (byte*)fnmatch_build_class_table(auStack_2a4, param_3);
          local_1a4 |= 0x40; local_18c = 1;
          break;
        case 0x63:
          local_1a4 |= 0x40; local_18c = 0;
          break;
        case 0x64: case 0x75:
          local_1a0 = 10;
        SET_UO:
          if (uVar5 > 0x6e) { local_18c = 4; break; }
          local_18c = 3;
          break;
        case 0x65: case 0x66: case 0x67:
          local_18c = 5;
          break;
        case 0x69:
          local_1a0 = 0;
          local_18c = 3;
          break;
        case 0x6e:
          if (-1 < (int)(local_1a4 << 0x1b)) {
            if ((local_1a4 & 1) == 0) {
              *(volatile int*)*local_2a8 = local_194;
              local_2a8 = local_2a8 + 1;
            } else {
              *(volatile short*)*local_2a8 = (short)local_194;
              local_2a8 = local_2a8 + 1;
            }
          }
          goto LAB_00078fae;
        case 0x6f:
          local_1a0 = 8; local_18c = 4;
          break;
        case 0x70:
          local_1a4 |= 0x220; local_1a0 = 0x10; local_18c = 4;
          break;
        case 0x73:
          local_18c = 2;
          break;
        default:
          local_18c = 3; local_1a0 = 10;
          break;
      }
    } else {
      pbVar6 = param_3;
      if (uVar5 == 0x25) goto LAB_00078ff8;
      if (uVar5 < 0x26) {
        if (uVar5 != 0) { local_18c = 3; local_1a0 = 10; goto LAB_00079156; }
        goto LAB_00079140;
      }
      if (uVar5 - 0x45 < 3) { local_18c = 5; goto LAB_00079156; }
      local_18c = 3; local_1a0 = 10;
    }
  } else {
    local_18c = 3; local_1a0 = 10;
  }

LAB_00079156:
  if (((int)param_2[1] < 1) && (iVar2 = local_24(param_1, param_2), iVar2 != 0))
    goto LAB_00079138;
  if (-1 < (int)(local_1a4 << 0x19)) {
    while ((int)((uint)(*(volatile byte*)(iVar1 + (uint)*(byte*)*param_2)) << 0x1c) < 0) {
      local_194 = local_194 + 1;
      iVar2 = param_2[1];
      param_2[1] = iVar2 - 1;
      if (iVar2 - 1 < 1) {
        iVar2 = local_24(param_1, param_2);
        if (iVar2 != 0) goto LAB_00079138;
      } else {
        *param_2 = *param_2 + 1;
      }
    }
  }
  if (local_18c < 3) {
    iVar2 = FUN_00079278(param_1, &local_1a4, param_2, &local_2a8);
  } else if (local_18c < 5) {
    iVar2 = FUN_0007932c(param_1, &local_1a4, param_2, &local_2a8);
  } else {
    iVar2 = param_1;
    if (*(volatile unsigned*)0x79274UL == 0) goto LAB_00078fae;
  }
  if (iVar2 == 1) return local_198;
  if (iVar2 == 2) {
  LAB_00079138:
    if ((local_198 == 0) || ((int)((uint)*(unsigned short*)(param_2 + 3) << 0x19) < 0)) {
    LAB_00079140:
      local_198 = -1;
    }
    return local_198;
  }
  goto LAB_00078fae;
}

