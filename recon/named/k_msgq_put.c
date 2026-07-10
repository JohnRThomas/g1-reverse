/* named: k_msgq_put */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed k_msgq_put @ 0x720d0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
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

static inline int ipsr(void){int r;__asm__ volatile("mrs %0, ipsr":"=r"(r));return r;}
static inline int rd_basepri(void){int r;__asm__ volatile("mrs %0, basepri":"=r"(r));return r;}
static inline void wr_basepri_max(int v){__asm__ volatile("msr basepri_max, %0"::"r"(v));}
static inline void isb(void){__asm__ volatile("isb 0xf":::"memory");}

unsigned k_msgq_put(int param_1, unsigned param_2, int param_3, int param_4)
{
    int iVar1; unsigned uVar2; unsigned uVar3; int iVar4; unsigned uVar5; int iVar6; unsigned uVar7; int bVar8; int iVar9;
    uVar3 = 0;
    bVar8 = ipsr();
    if(bVar8){ uVar3 = ipsr(); uVar3 = uVar3 & 0x1f; }
    if(uVar3==0 || (param_3==0 && param_4==0)){
        iVar6 = param_1 + 8;
        uVar7 = 0;
        bVar8 = ipsr();
        if(bVar8){ uVar7 = rd_basepri(); }
        bVar8 = ipsr();
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
                bVar8 = ipsr();
                if(bVar8){ wr_basepri_max(uVar7); }
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

