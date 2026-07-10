/* named: k_mem_slab_free */
/* Reconstructed k_mem_slab_free @ 0x71cf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_ready_thread_locked(void);
extern void z_reschedule(int,uint32_t);
extern int z_unpend_first_thread(int);
extern void assert_post_action(uint32_t,int);
extern void printk();
void k_mem_slab_free(int param_1, uint32_t* param_2){
    int iVar6=param_1+8;
    uint32_t uVar7=0;
    int iVar2=z_spin_lock_valid(iVar6);
    if(iVar2==0){
        printk(); printk();
        assert_post_action(uVar7,0x72);
        goto mainp;
    }
    z_spin_lock_set_owner(iVar6);
    {
        uint32_t* puVar5=*(uint32_t* volatile*)(param_1+0x14);
        int fail=0;
        if(param_2<puVar5) fail=1;
        else{
            uint32_t uVar4=*(volatile uint32_t*)(param_1+0x10);
            uint32_t diff=(uint32_t)((int)param_2-(int)puVar5);
            uint32_t q=uVar4?diff/uVar4:0;
            if(diff!=uVar4*q) fail=1;
            else if((uint32_t*)(uVar4*(*(volatile int*)(param_1+0xc)-1)+(int)puVar5)<param_2) fail=1;
        }
        if(fail){
            printk(); printk();
            assert_post_action(0,0x98);
            goto mainp;
        }
    }
mainp:;
    for(;;){
        int r8=*(volatile int*)(param_1+0x18);
        if(r8==0){
            int t=z_unpend_first_thread(param_1);
            if(t!=0){
                *(volatile int*)(t+0x90)=0;
                *(volatile uint32_t**)(t+0x14)=param_2;
                z_ready_thread_locked();
                z_reschedule(iVar6,uVar7);
                return;
            }
        }
        *param_2=*(volatile int*)(param_1+0x18);
        *(volatile uint32_t**)(param_1+0x18)=param_2;
        *(volatile int*)(param_1+0x1c)=*(volatile int*)(param_1+0x1c)-1;
        iVar2=z_spin_unlock_valid(iVar6);
        if(iVar2!=0) return;
        printk(); printk();
        assert_post_action(0,0xf0);
    }
}

