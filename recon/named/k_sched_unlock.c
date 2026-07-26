/* readable reconstruction; identity: FUN_00073b1c @ 0x00073b1c
 * public-name: k_sched_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_sched_unlock                           <= FUN_00073b1c @ 0x00073b1c
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
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f84f7                             @ 0x000f84f7
 *   rodata_f8522                             @ 0x000f8522
 *   _kernel                                  @ 0x2000b448
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_00073b1c @ 0x73b1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int z_spin_lock_valid(unsigned a);
extern int z_spin_unlock_valid(unsigned a);
extern void z_spin_lock_set_owner(unsigned a);
extern void assert_post_action(unsigned a, unsigned b);
extern void printk(unsigned a, unsigned b, unsigned c, unsigned d);
void k_sched_unlock(void){
    unsigned r4;
    r4 = __get_BASEPRI();
    unsigned tmp = 0x20;
    __set_BASEPRI_MAX(tmp);
    __ISB();
    int iVar3 = z_spin_lock_valid(0x2000b490);
    if (iVar3 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"),0x2000b490,0,0);
        assert_post_action(0x000f08c7,0x72);
        return;
    }
    z_spin_lock_set_owner(0x2000b490);
    unsigned ipsr;
    ipsr = __get_IPSR();
    if (ipsr != 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f801f,0x000f84f7,0xfd);
        printk(0x000f53ff,0,0,0);
        assert_post_action(0x000f84f7,0xfd);
        return;
    }
    int r2 = *(volatile int*)(0x2000b448 + 8);
    unsigned char cVar1 = *(volatile unsigned char*)(r2 + 0xf);
    if (cVar1 == 1){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f8522,0x000f84f7,0xfe);
        printk(0x000f53ff,0,0,0);
        assert_post_action(0x000f84f7,0xfe);
        return;
    }
    *(volatile unsigned char*)(r2 + 0xf) = (unsigned char)(cVar1 - 1);
    int iv = z_spin_unlock_valid(0x2000b490);
    if (iv == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0xf0);
        printk(((unsigned long)"\tNot my spinlock %p\n"),0x2000b490,0,0);
        assert_post_action(0x000f08c7,0xf0);
        return;
    }
    __set_BASEPRI(r4);
    __ISB();
    return;
}
