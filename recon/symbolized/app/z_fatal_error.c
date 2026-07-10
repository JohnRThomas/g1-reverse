#include "g1_app_symbols.h"
/* named: z_fatal_error */
/* Reconstructed z_fatal_error @ 0x71684  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned,unsigned,void*,int);
extern void arm_mpu_configure_partition_region(int);
extern void FUN_00063b7c(unsigned,int);
extern int k_current_get(void);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern char *posix_stub_zero(int);
void z_fatal_error(unsigned param_1, int param_2)
{
  unsigned basepri, uVar4; int iVar3; char *local_44;
  unsigned local_50, local_4c, uStack_48, local_40, local_28, local_24; unsigned short local_3c;
  uVar4 = 0;
  __asm__ volatile("mrs %0, basepri":"=r"(basepri));
  __asm__ volatile("msr basepri_max, %0"::"r"(0x20u));
  __asm__ volatile("isb");
  uVar4 = basepri;
  iVar3 = k_current_get();
  local_44 = (char*)"Unknown error" /*=0xf7c8e*/;
  if (param_1 < 5) local_44 = *(char**)(((uintptr_t)&rodata_98658) /*=0x98658*/ + param_1 * 4);
  local_3c = 0x301; local_4c = ">>> ZEPHYR FATAL ERROR %d: %s on CPU %d" /*=0xf7c9c*/; local_40 = 0; local_50 = 0x01000005; uStack_48 = param_1;
  FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x2c40, &local_50, 0);
  if ((param_2 != 0) && ((*(unsigned*)(param_2 + 0x1c) & 0x1ff) != 0)) {
    local_24 = "Fault during interrupt handling\n" /*=0xf7cc4*/; local_28 = 2;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_28, 0);
  }
  if (((iVar3 == 0) || (local_44 = posix_stub_zero(iVar3), local_44 == 0)) || (*local_44 == 0)) {
    local_44 = (char*)"unknown" /*=0xef596*/;
  }
  local_4c = "Current thread: %p (%s)" /*=0xf7ce5*/; local_40 = (local_40 & 0xffff0000) | 0x301; local_50 = 0x01000004; uStack_48 = iVar3;
  FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x2440, &local_50, 0);
  FUN_00063b7c(param_1, param_2);
  if (param_1 == 4) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "reason != K_ERR_KERNEL_PANIC" /*=0xf7d1f*/, "WEST_TOPDIR/zephyr/kernel/fatal.c" /*=0xf7cfd*/, 0x93);
    printk("\tAttempted to recover from a kernel panic condition\n" /*=0xf7d3c*/, 0, 0, 0);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/fatal.c" /*=0xf7cfd*/, 0x93);
  }
  __asm__ volatile("msr basepri, %0"::"r"(uVar4));
  __asm__ volatile("isb");
  arm_mpu_configure_partition_region(iVar3);
  return;
}

