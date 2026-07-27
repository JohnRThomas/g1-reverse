#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072908 @ 0x00072908
 * public-name: z_impl_k_sem_take
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
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
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f8198                             @ 0x000f8198
 *   rodata_f81b8                             @ 0x000f81b8
 *   g_mutex_lock_spinlock                    @ 0x2000b474
 */
/* Reconstructed FUN_00072908 @ 0x72908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_log.h"
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(uint32_t);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_pend_curr(uint32_t,uint32_t,int,uint32_t,uint32_t,uint32_t);
extern int assert_post_action(int, int);

int z_impl_k_sem_take(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
    uint32_t ipsr, bp, v; int iVar2; int r3;
    ipsr = __get_IPSR();
    if (ipsr != 0 && (param_3 | param_4) != 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f81b8) /*=0xf81b8*/,((unsigned long)&rodata_f8198) /*=0xf8198*/,0x80,(uint32_t)param_1,param_2,param_3);
        printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
        assert_post_action(((unsigned long)&rodata_f8198) /*=0xf8198*/,0x80);
        goto L936;
    }
  L936:
    bp = __get_BASEPRI();
    v = 0x20;
    __set_BASEPRI_MAX(v);
    __ISB();
    iVar2 = z_spin_lock_valid(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
    if (iVar2 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,(uint32_t)param_1,param_2,param_3);
        printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
        goto L936;
    }
    z_spin_lock_set_owner(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
    r3 = *(volatile int*)(param_1+8);
    if (r3 == 0){
        if ((param_3 | param_4) != 0){
            return z_pend_curr(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/, bp, param_1, param_3|param_4, param_3, param_4);
        }
        iVar2 = z_spin_unlock_valid(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
        if (iVar2 != 0){
            __set_BASEPRI(bp);
            __ISB();
            return 0xfffffff0;
        }
    } else {
        *(volatile int*)(param_1+8) = r3 - 1;
        iVar2 = z_spin_unlock_valid(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
        if (iVar2 != 0){
            __set_BASEPRI(bp);
            __ISB();
            return 0;
        }
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,(uint32_t)param_1,param_2,param_3);
    printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
    goto L936;
}
