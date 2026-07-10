/* named: net_buf_slist_put */
/* Reconstructed net_buf_slist_put @ 0x5f074  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

void net_buf_slist_put(uint32_t *param_1, uint32_t *param_2){
    unsigned uVar3=0, uVar5;
    if (param_1 == 0){
        printk(0x00099cbd,0x000f3630,0x000f539a,0x1ad);
        uVar5=0x1ad; uVar3=0x000f539a;
    } else if (param_2 == 0){
        printk(0x00099cbd,0x000f45be,0x000f539a,0x1ae);
        uVar5=0x1ae; uVar3=0x000f539a;
    } else {
        int iVar4 = z_spin_lock_valid((void*)0x2000b004);
        if (iVar4==0){
            printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
            printk(0x000f0935,0x2000b004);
            uVar5=0x72; uVar3=0x000f08c7;
        } else {
            z_spin_lock_set_owner((void*)0x2000b004);
            *param_2 = 0;
            if (param_1[1]==0){
                param_1[0] = (uint32_t)param_2;
                param_1[1] = (uint32_t)param_2;
            } else {
                *((uint32_t*)param_1[1]) = (uint32_t)param_2;
                param_1[1] = (uint32_t)param_2;
            }
            iVar4 = z_spin_unlock_valid((void*)0x2000b004);
            if (iVar4 != 0){
                return;
            }
            printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
            printk(0x000f090b,0x2000b004);
            uVar5=0xf0; uVar3=0x000f08c7;
        }
    }
    assert_post_action(uVar3,uVar5);
}

