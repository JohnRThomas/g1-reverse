/* readable reconstruction; identity: FUN_000727ac @ 0x000727ac
 * public-name: net_buf_pool_get_727ac
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   net_buf_pool_get_727ac                   <= FUN_000727ac @ 0x000727ac
 *   z_pend_curr                              <= FUN_00073f6c @ 0x00073f6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000727ac @ 0x727ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern int z_pend_curr(void*,unsigned,void*,unsigned,unsigned,unsigned,unsigned);
extern uintptr_t g1_recon_tagged_heap_node_release(unsigned *node, int release);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

uint32_t net_buf_pool_get_727ac(unsigned *param_1, unsigned param_2, unsigned param_3, unsigned param_4){
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
            int r = z_pend_curr(puVar7, uVar8, param_1+3, param_3|param_4, param_3, param_4, param_3);
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
        uVar3 = (unsigned)g1_recon_tagged_heap_node_release(puVar6, 1);
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
