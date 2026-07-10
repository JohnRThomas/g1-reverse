/* named: FUN_0005f654 */
/* Reconstructed FUN_0005f654 @ 0x5f654  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d944(unsigned,unsigned,void*,int);
unsigned FUN_0005f654(unsigned param_1, unsigned char *param_2)
{
  unsigned short uVar1;
  int iVar2, iVar5;
  unsigned uVar3, uVar4;
  unsigned local_18, local_14;
  uVar4 = param_2[4] & 0x1f;
  if (7 < uVar4) return 0xffffffea;
  uVar3 = (unsigned)*param_2;
  switch(uVar3) {
  case 0: case 1: case 2: case 3: break;
  default: local_14 = 0x000f5503; goto LAB;
  case 5: uVar3 = 4; break;
  case 8: uVar3 = 5; break;
  case 9: uVar3 = 6; break;
  case 0xb: uVar3 = 7;
  }
  if (param_2[1] == 3) { iVar5 = 1; }
  else {
    local_14 = 0x000f5522;
    if (param_2[1] != 4) goto LAB;
    iVar5 = 0;
  }
  uVar1 = *(unsigned short*)(param_2 + 2);
  if (uVar1 != 0x400a) {
    local_14 = 0x000f5546;
    if (0x400a < uVar1) {
      if (uVar1 == 0x4014) iVar2 = 4;
      else if (uVar1 == 0x4028) iVar2 = 5;
      else { if (uVar1 != 0x400f) goto LAB; iVar2 = 3; }
      goto LAB2;
    }
    if (uVar1 == 0x4003) { iVar2 = 0; goto LAB2; }
    if (uVar1 == 0x4005) { iVar2 = 1; goto LAB2; }
    if (uVar1 != 0) {
LAB:
      local_18 = 2;
      FUN_0004d944(0x000880e0, 0x1040, &local_18, 0);
      return 0xffffffea;
    }
  }
  iVar2 = 2;
LAB2:
  *(volatile unsigned*)(uVar4 * 0x10 + 0x5000e518) =
      uVar3 << 8 | (((unsigned)param_2[4] << 0x1a) >> 0x1f) << 0x14 | iVar5 << 0xc | iVar2 << 0x10;
  *(volatile unsigned*)(uVar4 * 0x10 + 0x5000e514) = (unsigned)param_2[6];
  *(volatile unsigned*)(uVar4 * 0x10 + 0x5000e510) = 0;
  *(volatile unsigned char*)(0x20002190 + uVar4 + 0xa0) = param_2[5];
  return 0;
}

