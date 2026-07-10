/* Reconstructed FUN_00071684 @ 0x71684  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned,unsigned,void*,int);
extern void FUN_00050b8c(int);
extern void FUN_00063b7c(unsigned,int);
extern int FUN_000748ac(void);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned);
extern char *FUN_00086418(int);
void FUN_00071684(unsigned param_1, int param_2)
{
  unsigned basepri, uVar4; int iVar3; char *local_44;
  unsigned local_50, local_4c, uStack_48, local_40, local_28, local_24; unsigned short local_3c;
  uVar4 = 0;
  __asm__ volatile("mrs %0, basepri":"=r"(basepri));
  __asm__ volatile("msr basepri_max, %0"::"r"(0x20u));
  __asm__ volatile("isb");
  uVar4 = basepri;
  iVar3 = FUN_000748ac();
  local_44 = (char*)0x000f7c8e;
  if (param_1 < 5) local_44 = *(char**)(0x00098658 + param_1 * 4);
  local_3c = 0x301; local_4c = 0x000f7c9c; local_40 = 0; local_50 = 0x01000005; uStack_48 = param_1;
  FUN_0004d944(0x00088258, 0x2c40, &local_50, 0);
  if ((param_2 != 0) && ((*(unsigned*)(param_2 + 0x1c) & 0x1ff) != 0)) {
    local_24 = 0x000f7cc4; local_28 = 2;
    FUN_0004d944(0x00088258, 0x1040, &local_28, 0);
  }
  if (((iVar3 == 0) || (local_44 = FUN_00086418(iVar3), local_44 == 0)) || (*local_44 == 0)) {
    local_44 = (char*)0x000ef596;
  }
  local_4c = 0x000f7ce5; local_40 = (local_40 & 0xffff0000) | 0x301; local_50 = 0x01000004; uStack_48 = iVar3;
  FUN_0004d944(0x00088258, 0x2440, &local_50, 0);
  FUN_00063b7c(param_1, param_2);
  if (param_1 == 4) {
    FUN_0007e2fa(0x00099cbd, 0x000f7d1f, 0x000f7cfd, 0x93);
    FUN_0007e2fa(0x000f7d3c, 0, 0, 0);
    FUN_0007e2ec(0x000f7cfd, 0x93);
  }
  __asm__ volatile("msr basepri, %0"::"r"(uVar4));
  __asm__ volatile("isb");
  FUN_00050b8c(iVar3);
  return;
}

