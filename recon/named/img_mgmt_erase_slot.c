/* readable reconstruction; identity: FUN_000516ac @ 0x000516ac
 * public-name: img_mgmt_erase_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_flash_area_id                   <= FUN_0005169c @ 0x0005169c
 *   img_mgmt_erase_slot                      <= FUN_000516ac @ 0x000516ac
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_read                          <= FUN_0007ef80 @ 0x0007ef80
 *   flash_area_erase                         <= FUN_0007efd4 @ 0x0007efd4
 *   flash_area_erased_val                    <= FUN_0007f012 @ 0x0007f012
 *   z_log_msg_static_create_img_mgmt         <= FUN_0008096a @ 0x0008096a
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_f261f                             @ 0x000f261f
 *   rodata_f2634                             @ 0x000f2634
 *   rodata_f270e                             @ 0x000f270e
 */
/* Reconstructed FUN_000516ac @ 0x516ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int flash_area_open(int,...);
extern int img_mgmt_flash_area_id(int);
extern int __assert_func(int,...);
extern int nullsub_3(int,...);
extern int flash_area_read(int,...);
extern int flash_area_erase(int,...);
extern int flash_area_erased_val(int,...);
extern int z_log_msg_static_create_img_mgmt(int,...);
int img_mgmt_erase_slot(int param_1)
{
  unsigned int uVar1;
  int iVar5;
  int local_6c, local_64;
  int aiStack_60[17];
  int dummy[16];
  uVar1 = (unsigned int)img_mgmt_flash_area_id(param_1);
  if ((int)uVar1 < 0) {
    iVar5 = 0xe;
  } else {
    local_6c = flash_area_open(uVar1 & 0xff, &local_64);
    iVar5 = local_64;
    if (local_6c < 0) {
      z_log_msg_static_create_img_mgmt(0x88208, 0x2040, dummy);
      iVar5 = 10;
    } else {
      uVar1 = *(volatile unsigned int*)(local_64 + 8) & 3;
      if (uVar1 != 0) __assert_func(0xf2634, 0x43, 0xf270e, 0xf261f);
      int iVar2 = flash_area_erased_val(iVar5);
      int iVar7 = *(volatile int*)(iVar5 + 8);
      for (; (int)uVar1 < iVar7; uVar1 = uVar1 + 0x40) {
        int iVar6 = iVar7 - uVar1;
        if (0x3f < iVar6) iVar6 = 0x40;
        int iVar3 = flash_area_read(iVar5, uVar1, aiStack_60, iVar6);
        if (iVar3 < 0) {
          z_log_msg_static_create_img_mgmt(0x88208, 0x1840, dummy);
          iVar5 = 0xb;
          goto LAB;
        }
        int *piVar4 = aiStack_60;
        for (iVar3 = 0; iVar3 != iVar6 >> 2; iVar3 = iVar3 + 1) {
          if (*piVar4 != iVar2 * 0x1010101) {
            iVar5 = flash_area_erase(local_64, 0, *(volatile int*)(local_64 + 8));
            if (iVar5 != 0) {
              z_log_msg_static_create_img_mgmt(0x88208, 0x1840, dummy);
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
