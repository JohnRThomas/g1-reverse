#include "g1_app_symbols.h"
/* named: arm_fault_dump_esf_registers */
/* Reconstructed arm_fault_dump_esf_registers @ 0x4ff6c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004d944(int,int,void*,int);
extern int z_fatal_error(int,int*);

void arm_fault_dump_esf_registers(int param_1, int *param_2, int param_3, int param_4)
{
  int uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_50;
  int local_4c;
  int iStack_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int iStack_2c;
  int uStack_28;

  uStack_28 = param_4;
  if (param_2 != 0) {
    local_38 = param_2[0];
    local_34 = param_2[1];
    local_30 = param_2[2];
    local_3c = "r0/a1:  0x%08x  r1/a2:  0x%08x  r2/a3:  0x%08x" /*=0xf1abb*/;
    local_40 = 5;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x2840, &local_40, 0);
    local_38 = param_2[3];
    local_34 = param_2[4];
    local_30 = param_2[5];
    local_3c = "r3/a4:  0x%08x r12/ip:  0x%08x r14/lr:  0x%08x" /*=0xf1aea*/;
    local_40 = 5;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x2840, &local_40, 0);
    local_30 = param_2[7];
    local_34 = " xpsr:  0x%08x" /*=0xf1b19*/;
    local_38 = 3;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1840, &local_38, 0);
    uVar1 = "s[%2d]:  0x%08x  s[%2d]:  0x%08x  s[%2d]:  0x%08x  s[%2d]:  0x%08x" /*=0xf1b28*/;
    iVar2 = 0;
    piVar4 = param_2;
    do {
      local_44 = piVar4[8];
      local_3c = piVar4[9];
      local_34 = piVar4[10];
      iStack_2c = piVar4[11];
      local_40 = iVar2 + 1;
      local_38 = iVar2 + 2;
      local_30 = iVar2 + 3;
      local_4c = uVar1;
      local_50 = 10;
      iVar3 = iVar2 + 4;
      iStack_48 = iVar2;
      FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x5040, &local_50, 0);
      piVar4 = piVar4 + 4;
      iVar2 = iVar3;
    } while (iVar3 != 0x10);
    local_30 = param_2[0x18];
    local_34 = "fpscr:  0x%08x" /*=0xf1b6b*/;
    local_38 = 3;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1840, &local_38, 0);
    local_30 = param_2[6];
    local_34 = "Faulting instruction address (r15/pc): 0x%08x" /*=0xf1b7a*/;
    local_38 = 3;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1840, &local_38, 0);
  }
  z_fatal_error(param_1, param_2);
}

