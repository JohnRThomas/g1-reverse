/* readable reconstruction; identity: FUN_00071cf4 @ 0x00071cf4
 * public-name: k_mem_slab_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f7e3c                             @ 0x000f7e3c
 *   rodata_f7e7e                             @ 0x000f7e7e
 *   rodata_f7f29                             @ 0x000f7f29
 */
/* Reconstructed FUN_00071cf4 @ 0x71cf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_ready_thread_locked(void);
extern void z_reschedule(int,uint32_t);
extern int z_unpend_first_thread(int);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,...);
void k_mem_slab_free(int param_1, uint32_t* param_2){
    int iVar6=param_1+8;
    uint32_t uVar7=0;
    int iVar2=z_spin_lock_valid(iVar6);
    if(iVar2==0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0xf08c7,0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"),iVar6);
        assert_post_action(0xf08c7,0x72);
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
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf7e7e,0xf7e3c,0x98);
            printk(0xf7f29);
            assert_post_action(0xf7e3c,0x98);
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
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0xf08c7,0xf0);
        printk(((unsigned long)"\tNot my spinlock %p\n"),iVar6);
        assert_post_action(0xf08c7,0xf0);
    }
}
