/* named: FUN_00073bf4 */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_00073bf4 @ 0x73bf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void FUN_000737d8(void);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_irqlock(unsigned);

void FUN_00073bf4(void){
    int iVar3 = z_spin_lock_valid((void*)0x2000b490);
    if (iVar3 == 0){
        printk(0x99cbd, 0x000f0920, 0x000f08c7, 0x72);
        printk(0x000f0935, 0x2000b490);
        assert_post_action(0x000f08c7, 0x72);
        return;
    }
    z_spin_lock_set_owner((void*)0x2000b490);
    char cVar1 = *(char*)(*(int*)(0x2000b448+8)+0xf);
    unsigned r2 = (unsigned)*(int*)(0x2000b448+8);
    unsigned r3 = (unsigned char)cVar1;
    if (cVar1 == 0){
        printk(0x99cbd, 0x000f8553, 0x000f82f4, 0x3f8);
        printk(0x000f53ff);
        assert_post_action(0x000f82f4, 0x3f8);
        r2 = 0x000f82f4;
        r3 = 0x3f8;
        /* fall through in emulation (ipsr==0) */
    }
    *(char*)(r2 + 0xf) = (char)(r3 + 1);
    FUN_000737d8();
    iVar3 = z_spin_unlock_valid((void*)0x2000b490);
    if (iVar3 != 0){
        z_reschedule_irqlock(0);
        return;
    }
    printk(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    printk(0x000f090b, 0x2000b490);
    assert_post_action(0x000f08c7, 0xf0);
}

