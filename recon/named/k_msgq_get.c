/* readable reconstruction; identity: FUN_00072240 @ 0x00072240
 * public-name: k_msgq_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
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
 *   g_zephyr_kernel                          @ 0x2000b448
 */
/* Reconstructed FUN_00072240 @ 0x72240  (parity: 48/300 trials, PROVEN) */
#include <stdint.h>
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
extern int memcpy(int,...);
static inline int ipsr(void){return (int)__get_IPSR();}
static inline int rd_basepri(void){return (int)__get_BASEPRI();}
static inline void wr_basepri_max(int v){__set_BASEPRI_MAX((uint32_t)v);}
static inline void isb(void){__ISB();}

int k_msgq_get(int param_1, unsigned param_2, int param_3, int param_4)
{
    int iVar1,iVar2; unsigned uVar3,uVar4; int iVar5,iVar6; unsigned uVar7; int bVar8; int iVar9;
    uVar4 = 0;
    bVar8 = ipsr();
    if(bVar8){ uVar4 = ipsr(); uVar4 &= 0x1f; }
    if(uVar4==0 || (param_3==0 && param_4==0)){
        iVar6 = param_1 + 8;
        uVar7 = 0;
        bVar8 = ipsr();
        if(bVar8){ uVar7 = rd_basepri(); }
        bVar8 = ipsr();
        if(bVar8 && (uVar4 = rd_basepri(), uVar4==0 || 0x20 < uVar4)){ wr_basepri_max(0x20); }
        isb();
        iVar5 = param_1; uVar3 = param_2; iVar9 = param_3;
        iVar1 = z_spin_lock_valid(iVar6);
        if(iVar1 == 0){
            printk(0x00099cbd,0x000f0920,0x000f08c7,0x72,iVar5,uVar3,iVar9);
            printk(0x000f0935,iVar6);
            uVar3 = 0x72; uVar7 = 0x000f08c7;
        } else {
            z_spin_lock_set_owner(iVar6);
            if(*(int*)(param_1+0x24) == 0){
                if(param_3 != 0 || param_4 != 0){
                    iVar5 = *(volatile int*)(0x2000b448+8);
                    *(unsigned*)(iVar5+0x14) = param_2;
                    iVar6 = FUN_00073f6c(iVar6,uVar7,param_1,iVar5,param_3,param_4);
                    return iVar6;
                }
                iVar1 = -0x23;
            } else {
                memcpy(param_2, *(unsigned*)(param_1+0x1c), *(unsigned*)(param_1+0xc));
                iVar1 = *(int*)(param_1+0x1c) + *(int*)(param_1+0xc);
                *(int*)(param_1+0x1c) = iVar1;
                bVar8 = (iVar1 == *(int*)(param_1+0x18));
                if(bVar8){ iVar1 = *(int*)(param_1+0x14); }
                if(bVar8){ *(int*)(param_1+0x1c) = iVar1; }
                *(int*)(param_1+0x24) = *(int*)(param_1+0x24) - 1;
                iVar1 = z_unpend_first_thread(param_1);
                if(iVar1 != 0){
                    uVar4 = *(unsigned*)(param_1+0x20);
                    if(*(unsigned*)(param_1+0x14) <= uVar4 && uVar4 < *(unsigned*)(param_1+0x18)){
                        memcpy(uVar4, *(unsigned*)(iVar1+0x14), *(unsigned*)(param_1+0xc));
                        iVar5 = *(int*)(param_1+0x20) + *(int*)(param_1+0xc);
                        *(int*)(param_1+0x20) = iVar5;
                        bVar8 = (iVar5 == *(int*)(param_1+0x18));
                        if(bVar8){ iVar5 = *(int*)(param_1+0x14); }
                        if(bVar8){ *(int*)(param_1+0x20) = iVar5; }
                        *(int*)(param_1+0x24) = *(int*)(param_1+0x24) + 1;
                        *(unsigned*)(iVar1+0x90) = 0;
                        z_ready_thread_locked(iVar1);
                        z_reschedule(iVar6,uVar7);
                        return 0;
                    }
                    printk(0x00099cbd,0x000f80ee,0x000f80cc,0xeb,iVar5,uVar3,iVar9);
                    uVar3 = 0xeb; uVar7 = 0x000f80cc;
                    goto LAB_000722a4;
                }
            }
            iVar2 = z_spin_unlock_valid(iVar6);
            if(iVar2 != 0){
                bVar8 = ipsr();
                if(bVar8){ wr_basepri_max(uVar7); }
                isb();
                return iVar1;
            }
            printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0,iVar5,uVar3,iVar9);
            printk(0x000f090b,iVar6);
            uVar3 = 0xf0; uVar7 = 0x000f08c7;
        }
    } else {
        printk(0x00099cbd,0x000f7df6,0x000f80cc,0xd2,param_1,param_2,param_3);
        printk(0x000f53ff);
        uVar3 = 0xd2; uVar7 = 0x000f80cc;
    }
LAB_000722a4:
    assert_post_action(uVar7,uVar3);
}
