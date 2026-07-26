#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005f148 @ 0x0005f148
 * public-name: net_buf_slist_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_slist_get                        <= FUN_0005f148 @ 0x0005f148
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f3630                             @ 0x000f3630
 *   rodata_f539a                             @ 0x000f539a
 *   g_net_buf_slist_lock                     @ 0x2000b004
 */
/* Reconstructed FUN_0005f148 @ 0x5f148  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
#include "../../headers/g1_cmsis_shim.h"
#include "../../headers/g1_log.h"
u32* net_buf_slist_get(u32* param_1){
    u32 uVar4, uVar6;
    if(param_1 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f3630) /*=0xf3630*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x1ba);
        uVar4=0x1ba; uVar6=((unsigned long)&rodata_f539a) /*=0xf539a*/;
    } else {
        uVar6 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = z_spin_lock_valid(((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
        if(iVar3==0){
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
            printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, ((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar4=0x72; uVar6=((unsigned long)&rodata_f08c7) /*=0xf08c7*/;
        } else {
            z_spin_lock_set_owner(((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
            u32* puVar5 = (u32*)*param_1;
            if(puVar5 != 0){
                uVar4 = *puVar5;
                *param_1 = uVar4;
                if(puVar5 == (u32*)param_1[1]) param_1[1] = uVar4;
            }
            iVar3 = z_spin_unlock_valid(((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
            if(iVar3!=0){
                wr_basepri(uVar6);
                isb_();
                return puVar5;
            }
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
            printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, ((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar4=0xf0; uVar6=((unsigned long)&rodata_f08c7) /*=0xf08c7*/;
        }
    }
    assert_post_action(uVar6, uVar4);
    return 0;
}
