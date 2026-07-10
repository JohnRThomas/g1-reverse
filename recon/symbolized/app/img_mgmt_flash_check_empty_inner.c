#include "g1_app_symbols.h"
/* named: img_mgmt_flash_check_empty_inner */
/* Reconstructed img_mgmt_flash_check_empty_inner @ 0x516ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int flash_area_open(int,...);
extern int FUN_0005169c(int,...);
extern int libc_fatal_error_and_abort(int,...);
extern int nullsub_3(int,...);
extern int flash_area_read(int,...);
extern int FUN_0007efd4(int,...);
extern int flash_area_erased_val(int,...);
extern int FUN_0008096a(int,...);
int img_mgmt_flash_check_empty_inner(void)
{
  unsigned int uVar1;
  int iVar5;
  int local_6c, local_64;
  int aiStack_60[17];
  int dummy[16];
  uVar1 = (unsigned int)FUN_0005169c(0);
  if ((int)uVar1 < 0) {
    iVar5 = 0xe;
  } else {
    local_6c = flash_area_open(uVar1 & 0xff, &local_64);
    iVar5 = local_64;
    if (local_6c < 0) {
      FUN_0008096a(((uintptr_t)&tbl_880d8) /*=0x88208*/, 0x2040, dummy);
      iVar5 = 10;
    } else {
      uVar1 = *(volatile unsigned int*)(local_64 + 8) & 3;
      if (uVar1 != 0) libc_fatal_error_and_abort("WEST_TOPDIR/zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/zephyr_img_mgmt.c" /*=0xf2634*/, 0x43, "img_mgmt_flash_check_empty_inner" /*=0xf270e*/, "fa->fa_size % 4 == 0" /*=0xf261f*/);
      int iVar2 = flash_area_erased_val(iVar5);
      int iVar7 = *(volatile int*)(iVar5 + 8);
      for (; (int)uVar1 < iVar7; uVar1 = uVar1 + 0x40) {
        int iVar6 = iVar7 - uVar1;
        if (0x3f < iVar6) iVar6 = 0x40;
        int iVar3 = flash_area_read(iVar5, uVar1, aiStack_60, iVar6);
        if (iVar3 < 0) {
          FUN_0008096a(((uintptr_t)&tbl_880d8) /*=0x88208*/, 0x1840, dummy);
          iVar5 = 0xb;
          goto LAB;
        }
        int *piVar4 = aiStack_60;
        for (iVar3 = 0; iVar3 != iVar6 >> 2; iVar3 = iVar3 + 1) {
          if (*piVar4 != iVar2 * 0x1010101) {
            iVar5 = FUN_0007efd4(local_64, 0, *(volatile int*)(local_64 + 8));
            if (iVar5 != 0) {
              FUN_0008096a(((uintptr_t)&tbl_880d8) /*=0x88208*/, 0x1840, dummy);
              iVar5 = 0xd;
            }
            goto LAB;
          }
          piVar4 = piVar4 + 1;
        }
      }
      iVar5 = 1;
    LAB:
      nullsub_3(local_64);
    }
  }
  return iVar5;
}

