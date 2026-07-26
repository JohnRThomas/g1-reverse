#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_sys_slist__param_0278                  [param_0278; library]
 * Raw function identity: 0x0005f074.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005f074 @ 0x0005f074
 * public-name: net_buf_slist_put
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_slist_put                        <= FUN_0005f074 @ 0x0005f074
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f3630                             @ 0x000f3630
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f539a                             @ 0x000f539a
 *   g_net_buf_slist_lock                     @ 0x2000b004
 */
/* Reconstructed FUN_0005f074 @ 0x5f074  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

void net_buf_slist_put(uint32_t *param_1, uint32_t *param_2){
    if (param_1 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f3630) /*=0xf3630*/,((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1ad);
        assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1ad);
    } else if (param_2 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f45be) /*=0xf45be*/,((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1ae);
        assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1ae);
    }

retry:
    {
        unsigned saved_priority = __get_BASEPRI();
        int iVar4;
        __set_BASEPRI_MAX(0x20);
        __ISB();
        iVar4 = z_spin_lock_valid((void*)((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
        if (iVar4==0) {
            printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0920) /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
            printk(((unsigned long)&rodata_f0935) /*=0xf0935*/,((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
            assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
            goto retry;
        }
        z_spin_lock_set_owner((void*)((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
        *param_2 = 0;
        if (param_1[1]==0){
            param_1[0] = (uint32_t)param_2;
            param_1[1] = (uint32_t)param_2;
        } else {
            *((uint32_t*)param_1[1]) = (uint32_t)param_2;
            param_1[1] = (uint32_t)param_2;
        }
        iVar4 = z_spin_unlock_valid((void*)((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
        if (iVar4 != 0){
            __set_BASEPRI(saved_priority);
            __ISB();
            return;
        }
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
        printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,((unsigned long)&g_net_buf_slist_lock) /*=0x2000b004*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
        goto retry;
    }
}
