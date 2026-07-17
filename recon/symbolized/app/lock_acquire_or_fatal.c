#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000510fc @ 0x000510fc
 * public-name: lock_acquire_or_fatal
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f22d5                             @ 0x000f22d5
 *   rodata_f23d4                             @ 0x000f23d4
 */
/* Reconstructed FUN_000510fc @ 0x510fc  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
extern void k_mutex_lock(int,int,int,int);
void lock_acquire_or_fatal(int param_1, int param_2)
{
    if (param_1 == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f23d4) /*=0xf23d4*/, ((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x1a6);
        assert_post_action(((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x1a6);
    }
    k_mutex_lock(param_1, param_2, -1, -1);
}
