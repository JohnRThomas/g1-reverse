/* readable reconstruction; identity: FUN_000720d0 @ 0x000720d0
 * public-name: k_msgq_put
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_handle_obj_poll_events                 <= FUN_0008688e @ 0x0008688e
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f7df6                             @ 0x000f7df6
 *   rodata_f80cc                             @ 0x000f80cc
 *   rodata_f80ee                             @ 0x000f80ee
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000720d0 @ 0x720d0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <stdbool.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int z_spin_lock_valid(int,...);
extern int z_spin_unlock_valid(int,...);
extern int z_spin_lock_set_owner(int,...);
extern int z_ready_thread_locked(int,...);
extern int z_reschedule(int,...);
extern int FUN_00073f6c(int,...);
extern int z_unpend_first_thread(int,...);
extern int assert_post_action(int,...) __attribute__((noreturn));
extern int printk(int,...);
extern int z_handle_obj_poll_events(int,...);
extern int memcpy(int,...);

/* This firmware entry is invoked in thread mode by its recovered callers. */
static inline __attribute__((always_inline)) unsigned ipsr(void){return __get_IPSR();}
static inline __attribute__((always_inline)) bool privileged(void)
{
    return ipsr() != 0 || (__get_CONTROL() & 1u) == 0;
}
static inline __attribute__((always_inline)) unsigned rd_basepri(void){return __get_BASEPRI();}
static inline __attribute__((always_inline)) void wr_basepri_max(unsigned v){__set_BASEPRI_MAX(v);}
static inline __attribute__((always_inline)) void wr_basepri(unsigned v){__set_BASEPRI(v);}
static inline __attribute__((always_inline)) void isb(void){__ISB();}

unsigned k_msgq_put(int param_1, unsigned param_2, int param_3, int param_4)
{
    int iVar1; unsigned uVar2; unsigned uVar3; int iVar4; unsigned uVar5; int iVar6; unsigned uVar7; int bVar8; int iVar9;
    uVar3 = 0;
    bVar8 = privileged();
    if(bVar8){ uVar3 = ipsr(); uVar3 = uVar3 & 0x1f; }
    if(uVar3==0 || (param_3==0 && param_4==0)){
        iVar6 = param_1 + 8;
        uVar7 = 0;
        bVar8 = privileged();
        if(bVar8){ uVar7 = rd_basepri(); }
        bVar8 = privileged();
        if(bVar8 && (uVar3 = rd_basepri(), uVar3==0 || 0x20 < uVar3)){
            wr_basepri_max(0x20);
        }
        isb();
        iVar4 = param_1; uVar2 = param_2; iVar9 = param_3;
        iVar1 = z_spin_lock_valid(iVar6);
        if(iVar1 == 0){
            printk(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72, iVar4, uVar2, iVar9);
            printk(0x000f0935, iVar6);
            uVar2 = 0x72; uVar7 = 0x000f08c7;
        } else {
            z_spin_lock_set_owner(iVar6);
            if(*(unsigned*)(param_1+0x24) < *(unsigned*)(param_1+0x10)){
                iVar1 = z_unpend_first_thread(param_1);
                if(iVar1 != 0){
                    memcpy(*(unsigned*)(iVar1+0x14), param_2, *(unsigned*)(param_1+0xc));
                    *(unsigned*)(iVar1+0x90) = 0;
                    z_ready_thread_locked(iVar1);
                    z_reschedule(iVar6, uVar7);
                    return 0;
                }
                uVar3 = *(unsigned*)(param_1+0x20);
                if(uVar3 < *(unsigned*)(param_1+0x14) || *(unsigned*)(param_1+0x18) <= uVar3){
                    printk(0x00099cbd, 0x000f80ee, 0x000f80cc, 0x90, iVar4, uVar2, iVar9);
                    uVar2 = 0x90; uVar7 = 0x000f80cc;
                    goto LAB_00072134;
                }
                memcpy(uVar3, param_2, *(unsigned*)(param_1+0xc));
                iVar1 = *(int*)(param_1+0x20) + *(int*)(param_1+0xc);
                *(int*)(param_1+0x20) = iVar1;
                bVar8 = (iVar1 == *(int*)(param_1+0x18));
                if(bVar8){ iVar1 = *(int*)(param_1+0x14); }
                if(bVar8){ *(int*)(param_1+0x20) = iVar1; }
                *(int*)(param_1+0x24) = *(int*)(param_1+0x24) + 1;
                z_handle_obj_poll_events(param_1+0x28, 0x10);
                uVar5 = 0;
            } else {
                if(param_3 != 0 || param_4 != 0){
                    iVar4 = *(volatile int*)(0x2000b448 + 8);
                    *(unsigned*)(iVar4+0x14) = param_2;
                    uVar7 = FUN_00073f6c(iVar6, uVar7, param_1, iVar4, param_3, param_4);
                    return uVar7;
                }
                uVar5 = 0xffffffdd;
            }
            iVar1 = z_spin_unlock_valid(iVar6);
            if(iVar1 != 0){
            bVar8 = privileged();
            if(bVar8){ wr_basepri(uVar7); }
                isb();
                return uVar5;
            }
            printk(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0, iVar4, uVar2, iVar9);
            printk(0x000f090b, iVar6);
            uVar2 = 0xf0; uVar7 = 0x000f08c7;
        }
    } else {
        printk(0x00099cbd, 0x000f7df6, 0x000f80cc, 0x76, param_1, param_2, param_3);
        printk(0x000f53ff);
        uVar2 = 0x76; uVar7 = 0x000f80cc;
    }
LAB_00072134:
    assert_post_action(uVar7, uVar2);
}
