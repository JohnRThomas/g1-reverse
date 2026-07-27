#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00071c20 @ 0x00071c20
 * public-name: k_mem_slab_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_pend_curr                              <= FUN_00073f6c @ 0x00073f6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00071c20 @ 0x71c20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(int);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_pend_curr(int,unsigned,int,int,int,int,int);
extern int assert_post_action(int, int);

int k_mem_slab_alloc(int param_1, int *param_2, int param_3, int param_4){
    int iVar6 = param_1 + 8;
    unsigned uVar7 = 0;
    int iVar3 = z_spin_lock_valid(iVar6);
    if (iVar3 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72, param_1, param_2);
        printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, iVar6);
        uVar7=0x72;
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, uVar7);
        return 0x72;
    }
    z_spin_lock_set_owner(iVar6);
    int *puVar4 = *(int**)(param_1+0x18);
    int ret;
    if (puVar4 == 0){
        if (param_3 != 0 || param_4 != 0){
            int r = z_pend_curr(iVar6, uVar7, param_1, 0, param_3, param_4, param_3);
            if (r != 0) return r;
            *param_2 = *(int*)(*(int*)(((unsigned long)&_kernel) /*=0x2000b448*/+8)+0x14);
            return 0;
        }
        ret = -0xc;
        *param_2 = 0;
    } else {
        *param_2 = (int)puVar4;
        *(int*)(param_1+0x18) = *puVar4;
        *(int*)(param_1+0x1c) = *(int*)(param_1+0x1c) + 1;
        ret = 0;
    }
    iVar3 = z_spin_unlock_valid(iVar6);
    if (iVar3 != 0){
        return ret;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0, param_1, param_2);
    printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, iVar6);
    uVar7=0xf0;
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, uVar7);
    return ret;
}
