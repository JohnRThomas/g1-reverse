/* named: img_mgmt_state_set_pending */
/* Reconstructed img_mgmt_state_set_pending @ 0x51d8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d944(int,...);
extern int flash_area_open(int,...);
extern int FUN_0005169c(int,...);
extern int FUN_00051c68(int,...);
extern int boot_set_next(int,...);
extern int nullsub_3(int,...);
extern int FUN_000809b0(int,...);
extern int FUN_00080a46(int,...);
extern int FUN_00080a4a(int,...);
int img_mgmt_state_set_pending(unsigned int param_1, int param_2)
{
  char local_25;
  int local_24;
  unsigned int uVar2, uVar3;
  int iVar4, iVar5, bVar6;
  int dummy[16];
  uVar2 = param_1;
  if (3 < param_1) uVar2 = (unsigned int)FUN_00051c68(0);
  iVar5 = (int)uVar2 >> 1;
  uVar2 = (unsigned int)FUN_00080a46(iVar5);
  local_25 = 0;
  uVar3 = (unsigned int)FUN_000809b0(iVar5, &local_25);
  if (param_2 == 0) {
    if (uVar2 == param_1) return 0x21;
    if (local_25 == 1) {
      if (uVar3 == param_1) return 0;
      return 0x1c;
    }
    if (local_25 == 0) bVar6 = (uVar3 == param_1);
    else bVar6 = (local_25 == 2);
    goto LAB_51e08;
  }
  iVar4 = FUN_00080a4a(0);
  if (iVar4 == iVar5) {
    if (local_25 == 1) return 0x1c;
    if (local_25 == 0) {
      if (uVar3 == param_1) return 0;
      bVar6 = (uVar2 == param_1);
      goto LAB_51e08;
    }
    goto LAB_51de0;
  } else {
    if (uVar2 == param_1) return 0x20;
    if (local_25 == 1) return 0x1c;
    if (local_25 != 0) goto LAB_51de0;
  }
  if (uVar3 == param_1) return 0;
  goto LAB_51de4;
LAB_51de0:
  if (local_25 != 2) goto LAB_51de4;
  if (uVar3 == param_1) return 0;
  goto LAB_51de4;
LAB_51e08:
  if (bVar6) return 0x1c;
LAB_51de4:;
  unsigned char uVar1 = (unsigned char)FUN_0005169c(param_1);
  iVar5 = flash_area_open(uVar1, &local_24);
  if (iVar5 == 0) {
    iVar5 = boot_set_next(local_24, (uVar2 == param_1), param_2);
    if (iVar5 != 0) {
      FUN_0004d944(0x88208, 0x3040, dummy, 0);
      if (iVar5 == 1) iVar5 = 0xc;
      else if (iVar5 == 4) iVar5 = 0x1d;
      else if (iVar5 == 3) iVar5 = 0x17;
      else iVar5 = 1;
    }
    nullsub_3(local_24);
    return iVar5;
  }
  return 10;
}

