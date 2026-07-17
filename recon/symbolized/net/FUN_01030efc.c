#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01030efc @ 0x01030efc
 * public-name: FUN_01030efc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01030efc @ 0x1030efc  (parity 300 trials PROVEN) */
typedef unsigned int undefined4;
typedef unsigned int uint;

undefined4 FUN_01030efc(int param_1,uint *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;

  if (*(char *)((int)param_2 + 5) == '\x01') {
    uVar8 = 0;
  }
  else {
    if (*(char *)((int)param_2 + 5) != '\x03') {
      return 0xffffff7a;
    }
    uVar8 = 0x10;
  }
  if (*(char *)((int)param_2 + 6) != '\x03') {
    return 0xffffff7a;
  }
  uVar7 = (uint)*(unsigned char *)((int)param_2 + 7);
  if ((uVar7 != 0) && (uVar7 != 1)) {
    return 0xffffff7a;
  }
  cVar1 = (char)param_2[1];
  if (cVar1 == '\x01') {
    uVar5 = 0x100;
  }
  else {
    if (cVar1 != '\x02') {
      if (cVar1 != '\0') {
        return 0xffffff7a;
      }
      uVar2 = 0;
      uVar5 = 0;
      goto LAB_01030f26;
    }
    uVar5 = 0;
  }
  uVar2 = 0xe;
LAB_01030f26:
  uVar3 = *param_2;
  if (uVar3 == 0x9600) {
    uVar4 = 0x9d0000;
  }
  else if (uVar3 < 0x9601) {
    uVar4 = 0x00275000;
    if (uVar3 != 0x2580) {
      if (uVar3 < 0x2581) {
        if (uVar3 == 0x4b0) {
          uVar4 = 0x4f000;
        }
        else if (uVar3 < 0x4b1) {
          if (uVar3 == 300) {
            uVar4 = 0x14000;
          }
          else {
            if (uVar3 != 600) {
              return 0xffffff7a;
            }
            uVar4 = 0x27000;
          }
        }
        else if (uVar3 == 0x960) {
          uVar4 = 0x9d000;
        }
        else {
          uVar4 = 0x0013b000;
          if (uVar3 != 0x12c0) {
            return 0xffffff7a;
          }
        }
      }
      else {
        uVar4 = 0x0075c000;
        if (uVar3 != 0x7080) {
          if (uVar3 < 0x7081) {
            uVar4 = 0x003af000;
            if ((uVar3 != 0x3840) && (uVar4 = 0x004ea000, uVar3 != 0x4b00)) {
              return 0xffffff7a;
            }
          }
          else {
            if (uVar3 != 0x7a12) {
              return 0xffffff7a;
            }
            uVar4 = 0x800000;
          }
        }
      }
    }
  }
  else if (uVar3 == 0x38400) {
    uVar4 = 0x3b00000;
  }
  else if (uVar3 < 0x38401) {
    uVar4 = 0x013a9000;
    if (uVar3 != 0x12c00) {
      if (uVar3 < 0x12c01) {
        if (uVar3 == 56000) {
          uVar4 = 0xe50000;
        }
        else {
          if (uVar3 != 0xe100) {
            return 0xffffff7a;
          }
          uVar4 = 0xeb0000;
        }
      }
      else {
        if (uVar3 != 0x1c200) {
          return 0xffffff7a;
        }
        uVar4 = 0x1d60000;
      }
    }
  }
  else if (uVar3 == 0xe1000) {
    uVar4 = 0xf000000;
  }
  else if (uVar3 < 0xe1001) {
    if (uVar3 == 0x0003d090) {
      uVar4 = 0x4000000;
    }
    else {
      if (uVar3 != 0x70800) {
        return 0xffffff7a;
      }
      uVar4 = 0x7400000;
    }
  }
  else {
    if (uVar3 != 0x000f4240) {
      return 0xffffff7a;
    }
    uVar4 = 0x10000000;
  }
  iVar6 = *(int *)(param_1 + 0x10);
  *(undefined4 *)(**(int **)(param_1 + 4) + 0x524) = uVar4;
  *(uint *)(**(int **)(param_1 + 4) + 0x56c) = uVar2 | uVar8 | uVar5 | uVar7;
  uVar8 = param_2[1];
  *(uint *)(iVar6 + 4) = *param_2;
  *(uint *)(iVar6 + 8) = uVar8;
  return 0;
}
