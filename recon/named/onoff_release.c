/* readable reconstruction; identity: FUN_0004ba38 @ 0x0004ba38
 * public-name: onoff_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_process_event                      <= FUN_0004b4fc @ 0x0004b4fc
 *   onoff_release                            <= FUN_0004ba38 @ 0x0004ba38
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0824                             @ 0x000f0824
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f094b                             @ 0x000f094b   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004ba38 @ 0x4ba38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int onoff_process_event(int,int,unsigned,int,unsigned);
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(int);
extern int z_spin_lock_set_owner(unsigned int*);
extern int assert_post_action(int, int);

unsigned onoff_release(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    int iVar7 = param_1 + 0x14;
    unsigned uVar8 = 0;
    int iVar4 = z_spin_lock_valid(iVar7);
    unsigned uVar5 = 0;
    if (iVar4 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_lock_valid(l)"), 0x000f08c7, 0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"), iVar7);
        uVar5=0x72; uVar8=0x000f08c7;
        assert_post_action(uVar8, uVar5);
        return uVar5;
    }
    z_spin_lock_set_owner(iVar7);
    unsigned uVar6 = *(unsigned short*)(param_1+0x1c) & 7;
    if (uVar6 == 2){
        short sVar1 = *(short*)(param_1+0x1e);
        if (sVar1 == 0){
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"mgr->refs > 0"), 0x000f0824, 0x1ef);
            assert_post_action(0x000f0824, 0x1ef);
        }
        unsigned short nv = (unsigned short)(sVar1 - 1);
        *(short*)(param_1+0x1e) = (short)nv;
        uVar5 = 2;
        if (nv == 0){
            onoff_process_event(param_1, 2, uVar8, 0, param_4);
            return 2;
        }
    } else if (uVar6 == 1){
        uVar5 = 0xfffffffb;
    } else {
        uVar5 = 0xffffff7a;
    }
    iVar4 = z_spin_unlock_valid(iVar7);
    if (iVar4 != 0){
        return uVar5;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_unlock_valid(l)"), 0x000f08c7, 0xf0);
    printk(((unsigned long)"\tNot my spinlock %p\n"), iVar7);
    uVar5=0xf0; uVar8=0x000f08c7;
    assert_post_action(uVar8, uVar5);
    return uVar5;
}
