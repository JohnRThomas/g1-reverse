#include "g1_net_symbols.h"
/* net-core FUN_0102fc30 @ 0x102fc30  (parity 300 trials PROVEN) */
#define C_0102fcbc ((uintptr_t)&g_net_bufpool_type0) /*=0x210009c8*/
#define C_0102fcc0 ((uintptr_t)&g_net_bufpool_type2) /*=0x21000994*/
#define C_0102fcb4 "RF_RPC_OS" /*=0x103ddcd*/
#define C_0102fcb8 ((uintptr_t)&rodata_103c024) /*=0x103c024*/

extern int FUN_0103a44c(int);
extern void FUN_01030014(int, int);
extern unsigned int FUN_0103a468(int);
extern void FUN_0103a478(int, int, unsigned int);
extern void FUN_0102ff94(int);
extern void FUN_0102e284(int, int, void *, int);

int FUN_0102fc30(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                  int param_5, unsigned int param_6)
{
  int iVar1;
  unsigned int uVar3;
  int iVar4;
  int local_30;
  int local_2c;
  int iStack_28;
  unsigned int uStack_20;
  unsigned int uVar2;

  uVar2 = C_0102fcbc;
  uStack_20 = param_4;
  if (param_1 == 0 || (uVar2 = C_0102fcc0, param_1 == 2)) {
    iVar1 = FUN_0103a44c((int)uVar2);
    if (iVar1 != 0) {
      iVar4 = iVar1 + 0xc;
      FUN_01030014(iVar4, 1);
      *(unsigned char *)(iVar1 + 0x18) = (unsigned char)param_1;
      if (param_5 == 0) {
        return iVar1;
      }
      if (param_6 == 0) {
        return iVar1;
      }
      uVar3 = FUN_0103a468(iVar4);
      if (param_6 <= uVar3) {
        FUN_0103a478(iVar4, param_5, param_6);
        return iVar1;
      }
      FUN_0102ff94(iVar1);
    }
  } else {
    local_2c = C_0102fcb4;
    local_30 = 3;
    iStack_28 = param_1;
    FUN_0102e284(C_0102fcb8, 0x1840, &local_30, 0);
  }
  return 0;
}

