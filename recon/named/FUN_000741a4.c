/* named: FUN_000741a4 */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_000741a4 @ 0x741a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void FUN_000737d8(int);
extern void dlist_unlink_node(void*,void*);
extern void FUN_00074d74(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_irqlock(unsigned);

void FUN_000741a4(uint8_t *param_1){
    unsigned uVar6=0;
    FUN_00074d74(param_1+0x18);
    int iVar4 = z_spin_lock_valid((void*)0x2000b490);
    if (iVar4==0){
        printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
        printk(0x000f0935,0x2000b490);
        uVar6=0x72;
        assert_post_action(0x000f08c7,uVar6);
        return;
    }
    z_spin_lock_set_owner((void*)0x2000b490);
    if ((int8_t)param_1[0xd] < 0){
        param_1[0xd] = param_1[0xd] & 0x7f;
        dlist_unlink_node((void*)0x2000b464, param_1);
    }
    int iVar5 = *(int*)(0x2000b448+8);
    param_1[0xd] = param_1[0xd] | 0x10;
    FUN_000737d8(iVar5 == (int)(intptr_t)param_1);
    iVar5 = z_spin_unlock_valid((void*)0x2000b490);
    if (iVar5 != 0){
        if (*(int*)(0x2000b448+8) != (int)(intptr_t)param_1) return;
        z_reschedule_irqlock(uVar6);
        return;
    }
    printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
    printk(0x000f090b,0x2000b490);
    uVar6=0xf0;
    assert_post_action(0x000f08c7,uVar6);
}

