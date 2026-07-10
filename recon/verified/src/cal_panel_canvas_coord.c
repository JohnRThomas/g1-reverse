/* Reconstructed cal_panel_canvas_coord @ 0x42fb0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned,unsigned,unsigned,int);
void cal_panel_canvas_coord(int *param_1, int *param_2)
{
  int iVar1, iVar3; char *pcVar2;
  if (param_1 != 0) {
    iVar3 = *param_1;
    iVar1 = FUN_000167a8();
    switch (*(unsigned char*)(iVar1+0xec1)) {
      case 1: iVar1 = 0x16; break;
      case 2: iVar1 = 8; break;
      default: iVar1 = 0; break;
      case 4: iVar1 = -4; break;
      case 5: iVar1 = -8; break;
      case 6: iVar1 = -10; break;
      case 7: iVar1 = -0xc; break;
      case 8: iVar1 = -0xe; break;
      case 9: iVar1 = -0x10; break;
    }
    *(volatile int*)param_1 = iVar1;
    pcVar2 = (char*)FUN_000167a8();
    if (*pcVar2 == 1) *(volatile int*)param_1 = -*(volatile int*)param_1;
    if ((*param_1 != iVar3) && (1 < *(int*)0x2000230c)) {
      if (*(int*)0x20007554 == 0) {
        iVar1 = FUN_000167a8();
        DEBUG_PRINT(0x000aa7a2, 0x000aa855, (unsigned)*(unsigned char*)(iVar1+0xec1), *param_1);
      } else {
        iVar1 = FUN_000167a8();
        FUN_00019c70(0x000aa7a2, 0x000aa855, (unsigned)*(unsigned char*)(iVar1+0xec1), *param_1);
      }
    }
  }
  if (param_2 != 0) {
    iVar3 = *param_2;
    iVar1 = FUN_000167a8();
    iVar1 = (8 - (unsigned)*(unsigned char*)(iVar1+0xec0)) * 0x23;
    *(volatile int*)param_2 = iVar1;
    if ((iVar1 - iVar3 != 0) && (1 < *(int*)0x2000230c)) {
      if (*(int*)0x20007554 == 0) {
        iVar1 = FUN_000167a8();
        DEBUG_PRINT(0x000aa7cb, 0x000aa855, (unsigned)*(unsigned char*)(iVar1+0xec0), *param_2);
        return;
      }
      iVar1 = FUN_000167a8();
      FUN_00019c70(0x000aa7cb, 0x000aa855, (unsigned)*(unsigned char*)(iVar1+0xec0), *param_2);
      return;
    }
  }
  return;
}

