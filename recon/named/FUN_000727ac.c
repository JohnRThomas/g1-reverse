/* named: FUN_000727ac */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_000727ac @ 0x727ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern int FUN_00073f6c(void*,unsigned,void*,unsigned,unsigned,unsigned,unsigned);
extern unsigned z_queue_node_peek(void*,int,void*,unsigned,void*,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

uint32_t FUN_000727ac(unsigned *param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned *puVar7 = param_1 + 2;
    unsigned uVar8 = 0;
    int iVar2 = z_spin_lock_valid(puVar7);
    if (iVar2 == 0){
        printk(0x99cbd, 0x000f0920, 0x000f08c7, 0x72);
        printk(0x000f0935, puVar7);
        uVar8=0x72;
        assert_post_action(0x000f08c7, uVar8);
        return 0x72;
    }
    z_spin_lock_set_owner(puVar7);
    unsigned *puVar6 = (unsigned*)*param_1;
    unsigned uVar3;
    if (puVar6 == 0){
        uVar3 = 0;
        if ((param_3 | param_4) != 0){
            int r = FUN_00073f6c(puVar7, uVar8, param_1+3, param_3|param_4, param_3, param_4, param_3);
            if (r != 0) return 0;
            return *(uint32_t*)(*(int*)(0x2000b448+8)+0x14);
        }
    } else {
        unsigned *puVar4 = (unsigned*)param_1[1];
        unsigned uVar5 = *puVar6 & 0xfffffffc;
        *param_1 = uVar5;
        if (puVar6 == puVar4){
            param_1[1] = uVar5;
        }
        uVar3 = z_queue_node_peek(puVar6, 1, puVar4, uVar5, param_1, param_2);
    }
    iVar2 = z_spin_unlock_valid(puVar7);
    if (iVar2 != 0){
        return uVar3;
    }
    printk(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    printk(0x000f090b, puVar7);
    uVar8=0xf0;
    assert_post_action(0x000f08c7, uVar8);
    return uVar3;
}

