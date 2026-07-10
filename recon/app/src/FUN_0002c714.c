/* Reconstructed FUN_0002c714 @ 0x2c714  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned char undefined1; typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_0002bffc(int,...);
extern int FUN_0002c0e8(void*,...);
extern int FUN_0002c30c(int,...);
extern int FUN_00033c04(int,...);
extern int FUN_00034410(int,...);
extern int FUN_0003443c(int,...);
extern int FUN_0003444c(int,...);
extern int sync_to_slave(void*,...);
extern int thunk_FUN_00074844(int,...);

undefined4 FUN_0002c714(char *param_1,int param_2,byte *param_3,undefined4 *param_4)
{
  byte bVar1; volatile int *piVar2; undefined1 uVar3; int iVar4=0; char *pcVar5;
  undefined4 uVar6; byte bVar7; short sVar8; uint uVar9; int bVar10;
  sVar8 = 1000;
  do {
    iVar4 = FUN_000167a8(0);
    if (*(char *)(iVar4 + 0xdd) == '\0') break;
    iVar4 = FUN_000167a8(0);
    iVar4 = FUN_00033c04(*(byte *)(iVar4 + 0xdd) - 1);
    if (iVar4 == 4) break;
    sVar8 = sVar8 + -1;
    thunk_FUN_00074844(0x21,0);
  } while (sVar8 != 0);
  uVar9 = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  FUN_0003443c(4);
  uVar3 = FUN_0002c30c(param_1[0xfea],0xf);
  piVar2 = (volatile int*)0x2000230c;
  *(undefined1 *)(param_2 + 7) = uVar3;
  do {
    while( 1 ) {
      if (param_1[0x108f] == '\0') { bVar10 = *param_3 == 1; }
      else { iVar4 = FUN_0003444c(0); bVar10 = iVar4 == 2; }
      if (((bVar10) || (*(char *)(param_2 + 7) == '\0')) && (param_1[0xfea] == '\n')) break;
      if (((param_1[1] == '\x01') || (iVar4 = FUN_000167a8(0), *(char *)(iVar4 + 1) == '\b')) ||
         (iVar4 = FUN_000167a8(0), *(char *)(iVar4 + 0xfea) == '\f')) {
        if (2 < *(volatile int*)0x2000230c) {
          if (*(volatile int*)0x20007554 == 0) {
            DEBUG_PRINT(0xa294a,0xa39d6,(uint)*(byte *)(param_2 + 1));
          } else { FUN_00019c70(0); }
        }
        FUN_0002c0e8(param_1);
        *param_4 = 0xa3311;
        FUN_0003443c(5);
        return 10;
      }
      if (*(char *)(param_2 + 1) != '\x04') {
        if (2 < *(volatile int*)0x2000230c) {
          if (*(volatile int*)0x20007554 == 0) {
            DEBUG_PRINT(0xa2977,0xa39d6,(uint)*(byte *)(param_2 + 1));
          } else { FUN_00019c70(0); }
        }
        if (*(char *)(param_2 + 1) != '\0') { return 0xb; }
        goto LAB_0002c884;
      }
      uVar9 = uVar9 + 1;
      if (((uVar9 & 0xf) == 0) && (2 < *piVar2)) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xa29be,0xa39d6,uVar9,**(undefined4 **)(param_1 + 0xff0),
                      (uint)*param_3,(uint)*(byte *)(param_2 + 9),(uint)*(byte *)(param_2 + 0xf),
                      *(undefined4 *)(param_2 + 0xb),(uint)*(byte *)(param_2 + 8));
        } else { FUN_00019c70(0); }
      }
      if (((param_1[0x108f] != '\0') && (*param_1 == '\x01')) &&
         (((uVar9 * 0xcccccccdU >> 2 | uVar9 * 0x40000000) ) <= 0x0ccccccc)) {
        bVar1 = *(byte *)(param_2 + 7);
        bVar7 = bVar1;
        if (bVar1 < 0x14) { bVar7 = bVar1 - 1; }
        if (bVar1 < 0x14) { *(byte *)(param_2 + 7) = bVar7; }
      }
LAB_0002c894:
      thunk_FUN_00074844(0x667,0);
    }
    if ((*(char *)(param_2 + 1) == '\x06') ||
       ((*(char *)(param_2 + 1) != '\x06' && (*param_3 == 2)))) {
      iVar4 = FUN_000167a8(0);
      if ((*(char *)(iVar4 + 0x108f) != '\0') &&
         (pcVar5 = (char *)FUN_000167a8(0), *pcVar5 == '\x01')) {
        iVar4 = FUN_000167a8(0);
        uVar9 = *(uint *)(iVar4 + 0x1060);
        *(uint *)(iVar4 + 0x1060) = uVar9 - 1000;
        *(uint *)(iVar4 + 0x1064) = *(int *)(iVar4 + 0x1064) + -1 + (uint)(999 < uVar9);
      }
      sync_to_slave(param_1,0xc,0);
      uVar6 = FUN_000167a8(0);
      FUN_0002bffc(uVar6,6,2);
      if (2 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xa28ee,0xa39d6,(uint)*(byte *)(param_2 + 1));
        } else { FUN_00019c70(0); }
      }
      return 0xb;
    }
    sync_to_slave(param_1,8,0);
    if (*param_1 == '\x01') { FUN_0002c0e8(param_1); }
    else if (*(char *)(param_2 + 1) == '\x04') goto LAB_0002c894;
    FUN_0003443c(5);
    if (*param_1 == '\x01') { thunk_FUN_00074844(0x4000,0); }
    iVar4 = FUN_00034410(0);
  } while (iVar4 == 4);
  if (2 < *(volatile int*)0x2000230c) {
    if (*(volatile int*)0x20007554 == 0) {
      DEBUG_PRINT(0xa291d,0xa39d6,(uint)*(byte *)(param_2 + 1));
    } else { FUN_00019c70(0); }
  }
LAB_0002c884:
  *param_4 = 0xa3311;
  return 10;
}

