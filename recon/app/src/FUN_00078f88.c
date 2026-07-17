/* Reconstructed FUN_00078f88 @ 0x78f88  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte;
typedef unsigned int uint;

extern int FUN_00079278(int, void*, void*, void*);
extern int FUN_0007932c(int, void*, void*, void*);
extern int FUN_00086bc8(int, int, int);
extern void *FUN_00087862(void*, void*);
extern void *FUN_0008789c(void*, void*);
typedef int (*fnptr)(int, void*);

int FUN_00078f88(int param_1, int *param_2, byte *param_3, int *param_4)
{
  int iVar1 = 0xf8a6bL;
  int iVar2;
  int iVar3;
  uint uVar4, uVar5;
  byte *pbVar6;
  int *local_2a8;
  unsigned char auStack_2a4[256];
  struct scan_conversion_state {
    uint flags;
    int base;
    uint width;
    int assignments;
    int consumed;
    unsigned char *scratch;
    int kind;
  } state;
  int local_28;
  fnptr local_24;

  local_28 = 0x877ed;
  local_24 = (fnptr)0x87863UL;
  local_2a8 = param_4;
  state.assignments = 0;
  state.consumed = 0;
  state.scratch = auStack_2a4;

LAB_00078fae:
  for (;;) {
    for (;;) {
      iVar2 = 0xf8b71L;
      uVar5 = (uint)*param_3;
      if (uVar5 == 0) return state.assignments;
      pbVar6 = param_3 + 1;
      uVar4 = (*(volatile byte*)(iVar1 + uVar5)) & 8;
      if (uVar4 == 0) break;
      param_3 = pbVar6;
      while (1) {
        if (!(0 < (int)param_2[1] || (iVar2 = local_24(param_1, param_2), iVar2 == 0))) break;
        if (!((int)((uint)(*(volatile byte*)(iVar1 + (uint)*(byte*)*param_2)) << 0x1c) < 0)) break;
        state.consumed = state.consumed + 1;
        *param_2 = *param_2 + 1;
        param_2[1] = param_2[1] - 1;
      }
    }
    if (uVar5 == 0x25) break;
  LAB_00078ff8:
    if (((int)param_2[1] < 1) && (iVar2 = local_24(param_1, param_2), iVar2 != 0))
      goto LAB_00079138;
    if (*(byte*)*param_2 != uVar5) return state.assignments;
    *param_2 = *param_2 + 1;
    param_2[1] = param_2[1] - 1;
    state.consumed = state.consumed + 1;
    param_3 = pbVar6;
  }
  state.flags = uVar4;
  state.width = uVar4;
  if (param_3[1] == 0x2a) {
    state.flags = 0x10;
    pbVar6 = param_3 + 2;
  }
  for (;;) {
    uVar5 = (uint)*pbVar6;
    if (uVar5 - 0x30 > 9) break;
    state.width = (state.width * 10 + uVar5) - 0x30;
    pbVar6 = pbVar6 + 1;
  }
  iVar3 = FUN_00086bc8(0xf8b71L, uVar5, 3);
  if (iVar3 != 0) {
    state.flags = (1 << ((iVar3 - iVar2) & 0xffU)) | state.flags;
    pbVar6 = pbVar6 + 1;
  }
  param_3 = pbVar6 + 1;
  uVar5 = (uint)*pbVar6;

  if (uVar5 < 0x79) {
    if (0x57 < uVar5) {
      switch (uVar5) {
        case 0x58: case 0x78:
          state.flags |= 0x200; state.base = 0x10;
          goto SET_UO;
        case 0x5b:
          param_3 = (byte*)FUN_0008789c(auStack_2a4, param_3);
          state.flags |= 0x40; state.kind = 1;
          break;
        case 0x63:
          state.flags |= 0x40; state.kind = 0;
          break;
        case 0x64: case 0x75:
          state.base = 10;
        SET_UO:
          if (uVar5 > 0x6e) { state.kind = 4; break; }
          state.kind = 3;
          break;
        case 0x65: case 0x66: case 0x67:
          state.kind = 5;
          break;
        case 0x69:
          state.base = 0;
          state.kind = 3;
          break;
        case 0x6e:
          if (-1 < (int)(state.flags << 0x1b)) {
            if ((state.flags & 1) == 0) {
              *(volatile int*)*local_2a8 = state.consumed;
              local_2a8 = local_2a8 + 1;
            } else {
              *(volatile short*)*local_2a8 = (short)state.consumed;
              local_2a8 = local_2a8 + 1;
            }
          }
          goto LAB_00078fae;
        case 0x6f:
          state.base = 8; state.kind = 4;
          break;
        case 0x70:
          state.flags |= 0x220; state.base = 0x10; state.kind = 4;
          break;
        case 0x73:
          state.kind = 2;
          break;
        default:
          state.kind = 3; state.base = 10;
          break;
      }
    } else {
      pbVar6 = param_3;
      if (uVar5 == 0x25) goto LAB_00078ff8;
      if (uVar5 < 0x26) {
        if (uVar5 != 0) { state.kind = 3; state.base = 10; goto LAB_00079156; }
        goto LAB_00079140;
      }
      if (uVar5 - 0x45 < 3) { state.kind = 5; goto LAB_00079156; }
      state.kind = 3; state.base = 10;
    }
  } else {
    state.kind = 3; state.base = 10;
  }

LAB_00079156:
  if (((int)param_2[1] < 1) && (iVar2 = local_24(param_1, param_2), iVar2 != 0))
    goto LAB_00079138;
  if (-1 < (int)(state.flags << 0x19)) {
    while ((int)((uint)(*(volatile byte*)(iVar1 + (uint)*(byte*)*param_2)) << 0x1c) < 0) {
      state.consumed = state.consumed + 1;
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
  if (state.kind < 3) {
    iVar2 = FUN_00079278(param_1, &state, param_2, &local_2a8);
  } else if (state.kind < 5) {
    iVar2 = FUN_0007932c(param_1, &state, param_2, &local_2a8);
  } else {
    iVar2 = param_1;
    if (*(volatile unsigned*)0x79274UL == 0) goto LAB_00078fae;
  }
  if (iVar2 == 1) return state.assignments;
  if (iVar2 == 2) {
  LAB_00079138:
    if ((state.assignments == 0) || ((int)((uint)*(unsigned short*)(param_2 + 3) << 0x19) < 0)) {
    LAB_00079140:
      state.assignments = -1;
    }
    return state.assignments;
  }
  goto LAB_00078fae;
}
