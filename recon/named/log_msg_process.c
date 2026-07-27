/* readable reconstruction; identity: FUN_0004d334 @ 0x0004d334
 * public-name: log_msg_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   activate_foreach_backend                 <= FUN_0004d2d0 @ 0x0004d2d0
 *   log_msg_process                          <= FUN_0004d334 @ 0x0004d334
 *   log_msg_commit                           <= FUN_0004d8f8 @ 0x0004d8f8
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_inc                               <= FUN_0007ee2c @ 0x0007ee2c
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0cdb                             @ 0x000f0cdb   [INLINED -- G6 literal batch]
 *   rodata_f0cff                             @ 0x000f0cff   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   z_log_process_guard                      @ 0x2000a0dc
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0004d334 @ 0x4d334  (parity: 300/300 trials, PROVEN) */
extern int atomic_inc(int);
extern unsigned int activate_foreach_backend(unsigned int);
extern void log_msg_commit(int*,unsigned,int);
extern void k_sleep(int,int);
extern int assert_post_action(int, int);
unsigned int log_msg_process(unsigned long param_1, unsigned long param_2) {
  int *piVar1 = (int*)0x000882b0;
  int *piVar5 = (int*)0x000882a0;
  unsigned uVar3, uVar6; int iVar2; unsigned uVar4;
  if ((unsigned)((int)piVar1 - (int)piVar5) < 0xa0){
    iVar2 = atomic_inc(0x2000a0dc);
    if (iVar2 != 0) return 0;
    uVar3=0; uVar6=0;
    for (; piVar5 <= piVar1; piVar5 += 4){
      if (piVar1 <= piVar5){
        if (param_1 != 0){
          while (uVar3 != 0){
            uVar3 = activate_foreach_backend(uVar3);
            if (param_2 != 0) k_sleep(0x148,0);
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
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"backend <= _log_backend_list_end"),0x000f0cae,0x126);
    printk(((unsigned long)"\tunexpected list end location\n"));
    uVar4 = 0x126;
  } else {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"log_backend_count_get() < (32 / 3U)"),0x000f0cae,0x119);
    uVar4 = 0x119;
  }
  assert_post_action(0x000f0cae,uVar4);
  return 0;
}
