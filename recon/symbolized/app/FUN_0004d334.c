#include "g1_app_symbols.h"
/* named: FUN_0004d334 */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
*/
/* Reconstructed FUN_0004d334 @ 0x4d334  (parity: 300/300 trials, PROVEN) */
extern int atomic_inc(int);
extern unsigned activate_foreach_backend(unsigned);
extern void log_msg_commit(int*,unsigned,int);
extern void FUN_00074844(int,int);
extern void printk(int,...);
extern void assert_post_action(int,...);
unsigned FUN_0004d334(int param_1,int param_2){
  int *piVar1 = (int*)((uintptr_t)&__settings_handler_static_list_start) /*=0x882b0*/;
  int *piVar5 = (int*)((uintptr_t)&tbl_880d8) /*=0x882a0*/;
  unsigned uVar3, uVar6; int iVar2; unsigned uVar4;
  if ((unsigned)((int)piVar1 - (int)piVar5) < 0xa0){
    iVar2 = atomic_inc(((uintptr_t)&z_log_process_guard) /*=0x2000a0dc*/);
    if (iVar2 != 0) return 0;
    uVar3=0; uVar6=0;
    for (; piVar5 <= piVar1; piVar5 += 4){
      if (piVar1 <= piVar5){
        if (param_1 != 0){
          while (uVar3 != 0){
            uVar3 = activate_foreach_backend(uVar3);
            if (param_2 != 0) FUN_00074844(0x148,0);
          }
          return 0;
        }
        return uVar3;
      }
      if ((char)piVar5[3] != 0){
        if (*(void(**)(int*))(*piVar5 + 0xc) != 0) (*(void(**)(int*))(*piVar5+0xc))(piVar5);
        if (*(int(**)(int*))(*piVar5+0x10)==0 || (iVar2=(*(int(**)(int*))(*piVar5+0x10))(piVar5))==0)
          log_msg_commit(piVar5, *(unsigned*)piVar5[1], 4);
        else uVar3 = uVar3 | (1u << (uVar6 & 0xff));
        uVar6++;
      }
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"backend <= _log_backend_list_end" /*=0xf0cff*/,"WEST_TOPDIR/zephyr/subsys/logging/log_core.c" /*=0xf0cae*/,0x126);
    printk("\tunexpected list end location\n" /*=0xf0d20*/);
    uVar4 = 0x126;
  } else {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"log_backend_count_get() < (32 / 3U)" /*=0xf0cdb*/,"WEST_TOPDIR/zephyr/subsys/logging/log_core.c" /*=0xf0cae*/,0x119);
    uVar4 = 0x119;
  }
  assert_post_action("WEST_TOPDIR/zephyr/subsys/logging/log_core.c" /*=0xf0cae*/,uVar4);
  return 0;
}

